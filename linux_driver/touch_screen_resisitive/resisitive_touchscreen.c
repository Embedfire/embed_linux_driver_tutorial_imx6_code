#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/module.h>
#include <linux/delay.h>
#include <linux/errno.h>
#include <linux/gpio/consumer.h>
#include <linux/input.h>
#include <linux/slab.h>
#include <linux/of.h>
#include <linux/of_address.h>
#include <linux/interrupt.h>
#include <linux/platform_device.h>
#include <linux/clk.h>

#include "imx6ull.h"

struct imx6ull_rests {
	struct device *dev;              /* 触摸屏驱动对应的设备 */
	struct input_dev *input_dev;     /* 输入设备 */
	struct imx6ull_tsc *tsc_regs;    /* imx6ull tsc控制器的寄存器 */
	struct imx6ull_adc *adc_regs;    /* imx6ull ADC的寄存器 */
	struct clk *tsc_clk;             /* tsc控制器时钟 */
	struct clk *adc_clk;             /* ADC时钟 */
	struct gpio_desc *xnur_gpio;     /* 辅助检测是否有触摸的gpio */

	unsigned int measure_delay_time; /* 测量延迟时间 */
	unsigned int pre_charge_time;    /* 电阻屏预充电时间 */
	bool average_enable;             /* 是否使能ADC硬件平均功能 */
	unsigned int average_select;     /* ADC的平均采样点 */
};

static bool imx6ull_adc_auto_calibration(struct imx6ull_rests *ts)
{
	struct imx6ull_adc *adc_regs = ts->adc_regs;
	unsigned int value;
		
	adc_regs->CFG &= ~(0x1 << 13);  /* 选择软件触发 */
	adc_regs->GS  |= (0x1 << 1);    /* 清除校准完成标记 */

	adc_regs->GC |= (0x1 << 7);     /* 启动ADC校准 */

	mdelay(100);                    /* 等待校准完成 */

	if (adc_regs->GC & (0x1 << 7))  /* 判断校准是否完成, 校准完成该寄存器的bit[7] 会自动清0*/
		return false;

	if (adc_regs->GS &  (0x1 << 1)) /* 判断是否校准完成，校准失败该寄存器的bit[1] 被置1 */
		return false;

	if ((adc_regs->HS & 0x01) == 0) /* 判断是否转换完成 */
		return false; 
	
	value = adc_regs->R[0];         /* 通过读adc_regs->R[0]清除adc_regs->HS转换完成标记 */

	adc_regs->CFG |= (0x1 << 13);   /* 选择硬件触发 */

	return true;
}

static int imx6ull_adc_init(struct imx6ull_rests *ts)
{
	struct imx6ull_adc *adc_regs = ts->adc_regs;

	adc_regs->CFG &= ~(0xf << 0);
	adc_regs->CFG |= (0x2 << 2);  /* 设置ADC的分辨率为12bit */
	adc_regs->CFG |= (0 << 0);    /* 选择ADC的时钟源，这里选择IPG clock */
	adc_regs->CFG |= (0x3 << 5);  /* 对ADC的时钟源进行8分频 */
	adc_regs->CFG &= ~(0x1 << 4); /* 设置为短采样模式 */
	
	if (ts->average_enable)
	{
		adc_regs->CFG &= ~(0x3 << 14);
		adc_regs->CFG |= (ts->average_select << 14); /* 设置平均采样点个数 */
	}

	if (ts->average_enable)
	{
		adc_regs->GC |= (0x1 << 5); /* 使能ADC硬件平均功能 */
	}


	adc_regs->HC[1] &= ~(0x1 <<7);  /* 禁止channel3转换完成中断 */
	adc_regs->HC[1] &= ~0x1F;
	adc_regs->HC[1] |= 0x03;        /* 配置channel3为xnur    */
	
	adc_regs->HC[3] &= ~(0x1 <<7);  /* 禁止channel1转换完成中断 */
	adc_regs->HC[3] &= ~0x1F;
	adc_regs->HC[3] |= 0x01;         /* 配置channel3为ynlr    */

	if(!imx6ull_adc_auto_calibration(ts))
	{
		dev_err(ts->dev, "ADC calibration failed\n");
		return -1;
	}

	return 0;
}


static int imx6ull_tsc_config(struct imx6ull_rests *ts)
{
 	struct imx6ull_tsc *tsc_regs = ts->tsc_regs;

	tsc_regs->BASIC_SETTING |= ts->measure_delay_time << 8;   /* 设置测量延迟时间 */
	tsc_regs->BASIC_SETTING &= ~(0x1 << 4);                   /* 设置4线检测模式 */
	tsc_regs->BASIC_SETTING |= (0x1 << 0);                    /* 使能自动测量 */
	
	tsc_regs->PS_INPUT_BUFFER_ADDR = ts->pre_charge_time;     /* 设置预充电时间 */
 
	tsc_regs->INT_EN = (0x1 << 0);                            /* 测量中断使能 */
 
	tsc_regs->INT_SIG_EN |= (0x1 << 0);                       /* 测量信号使能 */
	tsc_regs->INT_SIG_EN |= (0x1 << 8);                       /* 有效信号使能 */
	
	tsc_regs->FLOW_CONTROL |= (0x1 << 12);                    /* 启动触摸检测, 当检测到触摸时，开始测量 */
	tsc_regs->FLOW_CONTROL &= ~(0x1 << 16);                   /* 使能TSC */

	return 0;
}

static int imx6ull_tsc_disable(struct imx6ull_rests *ts)
{
	struct imx6ull_adc *adc_regs = ts->adc_regs;
	struct imx6ull_tsc *tsc_regs = ts->tsc_regs;
	
	/* tsc控制器进入空闲状态 */
	tsc_regs->FLOW_CONTROL |= (0x1 << 16);

	/* adc进入停止模式 */
	adc_regs->HC[0] |= 0x1f;

	return  0;
}

/* Delay some time (max 2ms), wait the pre-charge done. */
static bool tsc_wait_detect_mode(struct imx6ull_rests *ts)
{
	unsigned int state_machine;
	unsigned long timeout = jiffies + msecs_to_jiffies(2);
	struct imx6ull_tsc *tsc_regs = ts->tsc_regs;

	do {
		if (time_after(jiffies, timeout))
			return false;
		usleep_range(200, 400);
		state_machine = (tsc_regs->DEBUG_MODE2 >> 20) & 0x7;  /* 获取当前的机器状态 */
	} while (state_machine != 0x02);                          /* 判断是否在检测模式 */
	usleep_range(200, 400);
	return true;
}


static int imx6ull_tsc_init(struct imx6ull_rests *ts)
{
	imx6ull_adc_init(ts);
	imx6ull_tsc_config(ts);
	
	return 0;
}

static irqreturn_t tsc_irq_fn(int irq, void *dev_id)
{
	struct imx6ull_rests *ts = dev_id;
	unsigned int status;
	unsigned int value;
	unsigned int x;
	unsigned int y;
	
	/* 读取状态寄存器 */
	status = ts->tsc_regs->INT_STATUS;
	
	/* 清除坐标测量信号标记 */
	ts->tsc_regs->INT_STATUS = 0x01;

	/* 启动触摸检测 */
	ts->tsc_regs->FLOW_CONTROL |= (1 << 12);
	
	if (status & 0x1) 
	{                       
		value = ts->tsc_regs->MEASEURE_VALUE;  
		x = (value >> 16) & 0x0fff;            
		y = value & 0x0fff;                   

		if (!tsc_wait_detect_mode(ts) || gpiod_get_value_cansleep(ts->xnur_gpio)) 
		{
			input_report_key(ts->input_dev, BTN_TOUCH, 1);  /* 按下 */
			input_report_abs(ts->input_dev, ABS_X, x);
			input_report_abs(ts->input_dev, ABS_Y, y);
		}
		else 
		{
			input_report_key(ts->input_dev, BTN_TOUCH, 0);  /* 松开 */
		}

		input_sync(ts->input_dev);
	}

	return IRQ_HANDLED;
}


static int imx6ull_tsc_open(struct input_dev *input_dev)
{
	struct imx6ull_rests *tsc = input_get_drvdata(input_dev);
	int err;

	err = clk_prepare_enable(tsc->adc_clk);
	if (err) {
		dev_err(tsc->dev,
			"Could not prepare or enable the adc clock: %d\n",
			err);
		return err;
	}

	err = clk_prepare_enable(tsc->tsc_clk);
	if (err) {
		dev_err(tsc->dev,
			"Could not prepare or enable the tsc clock: %d\n",
			err);
		goto disable_adc_clk;
	}

	err = imx6ull_tsc_init(tsc);
	if (err)
		goto disable_tsc_clk;

	return 0;

disable_tsc_clk:
	clk_disable_unprepare(tsc->tsc_clk);
disable_adc_clk:
	clk_disable_unprepare(tsc->adc_clk);
	return err;
}

static void imx6ull_tsc_close(struct input_dev *input_dev)
{
	struct imx6ull_rests *tsc = input_get_drvdata(input_dev);

	imx6ull_tsc_disable(tsc);

	clk_disable_unprepare(tsc->tsc_clk);
	clk_disable_unprepare(tsc->adc_clk);
}

static int get_tsc_para_from_dt(struct device *dev, struct imx6ull_rests *ts)
{
	struct device_node *np = dev->of_node;
	unsigned int average_samples;
	int ret;

	ret = of_property_read_u32(np, "measure-delay-time", &ts->measure_delay_time);
	if (ret)
		ts->measure_delay_time = 0xffff;

	ret = of_property_read_u32(np, "pre-charge-time", &ts->pre_charge_time);
	if (ret)
		ts->pre_charge_time = 0xfff;

	ret = of_property_read_u32(np, "touchscreen-average-samples", &average_samples);
	if (ret)
		average_samples = 1;

	switch (average_samples) {
	case 1:
		ts->average_enable = false;
		ts->average_select = 0; /* value unused; initialize anyway */
		break;
	case 4:
	case 8:
	case 16:
	case 32:
		ts->average_enable = true;
		ts->average_select = ilog2(average_samples) - 2;
		break;
	default:
		dev_err(dev,"touchscreen-average-samples (%u) must be 1, 4, 8, 16 or 32\n", average_samples);
		return -EINVAL;
	}

	return 0;
}

static int res_ts_driver_probe(struct platform_device *pdev)
{
	struct device_node *np = pdev->dev.of_node;
	struct imx6ull_rests *ts;
	struct input_dev *input_dev;
	int err;
	int tsc_irq;

	ts = devm_kzalloc(&pdev->dev, sizeof(*ts), GFP_KERNEL);
	if (!ts)
		return -ENOMEM;
	
	input_dev = devm_input_allocate_device(&pdev->dev);
	if (!input_dev)
		return -ENOMEM;

	input_dev->name = "Fire Touchscreen Driver";
	
	input_dev->open = imx6ull_tsc_open;
	input_dev->close = imx6ull_tsc_close;

	input_set_capability(input_dev, EV_KEY, BTN_TOUCH);
	input_set_abs_params(input_dev, ABS_X, 0, 0xFFF, 0, 0);
	input_set_abs_params(input_dev, ABS_Y, 0, 0xFFF, 0, 0);

	input_set_drvdata(input_dev, ts);

	ts->dev = &pdev->dev;
	ts->input_dev = input_dev;

	ts->tsc_regs = devm_of_iomap(&pdev->dev, np, 0, NULL);
	if (IS_ERR(ts->tsc_regs)) {
		err = PTR_ERR(ts->tsc_regs);
		dev_err(&pdev->dev, "failed to remap tsc memory: %d\n", err);
		return err;
	}

	ts->adc_regs = devm_of_iomap(&pdev->dev, np, 1, NULL);
	if (IS_ERR(ts->adc_regs)) {
		err = PTR_ERR(ts->adc_regs);
		dev_err(&pdev->dev, "failed to remap adc memory: %d\n", err);
		return err;
	}

	ts->tsc_clk = devm_clk_get(&pdev->dev, "tsc");
	if (IS_ERR(ts->tsc_clk)) {
		err = PTR_ERR(ts->tsc_clk);
		dev_err(&pdev->dev, "failed getting tsc clock: %d\n", err);
		return err;
	}

	ts->adc_clk = devm_clk_get(&pdev->dev, "adc");
	if (IS_ERR(ts->adc_clk)) {
		err = PTR_ERR(ts->adc_clk);
		dev_err(&pdev->dev, "failed getting adc clock: %d\n", err);
		return err;
	}

	ts->xnur_gpio = devm_gpiod_get(&pdev->dev, "xnur", GPIOD_IN);
	if (IS_ERR(ts->xnur_gpio)) {
		err = PTR_ERR(ts->xnur_gpio);
		dev_err(&pdev->dev,
			"failed to request GPIO tsc_X- (xnur): %d\n", err);
		return err;
	}

	tsc_irq = platform_get_irq(pdev, 0);
	if (tsc_irq < 0) {
		dev_err(&pdev->dev, "no tsc irq resource?\n");
		return tsc_irq;
	}
	
	err = devm_request_threaded_irq(ts->dev, tsc_irq,NULL, tsc_irq_fn, IRQF_ONESHOT, dev_name(&pdev->dev), ts);
	if (err) {
		dev_err(&pdev->dev,
			"failed requesting tsc irq %d: %d\n",
			tsc_irq, err);
		return err;
	}

	get_tsc_para_from_dt(&pdev->dev, ts);

	err = input_register_device(ts->input_dev);
	if (err) {
		dev_err(&pdev->dev,
			"failed to register input device: %d\n", err);
		return err;
	}

	printk(KERN_EMERG"match success!\n");
	return 0;	
}


static struct of_device_id res_ts_of_match[] = {
	{.compatible = "fire,res_tsc",},
	{},
};
	

static struct platform_driver res_ts_drv = {
	.probe  = res_ts_driver_probe,
	.driver = {
		.name = "res_ts_drv",
		.of_match_table = res_ts_of_match,
	},
};


static int __init res_ts_driver_init(void)
{
	return platform_driver_register(&res_ts_drv);
}

static void __exit res_ts_driver_exit(void)
{
	platform_driver_unregister(&res_ts_drv);
}

module_init(res_ts_driver_init);
module_exit(res_ts_driver_exit);
MODULE_LICENSE("GPL");


