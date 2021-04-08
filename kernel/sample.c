// SPDX-License-Identifier: GPL-2.0+

#include <linux/module.h>

static int __init sample_init(void)
{
	int ret;

	pr_info("hello %s\n", __func__);

	ret = 0;
	return ret;
}

static void __exit sample_exit(void)
{
	pr_info("byebye %s\n", __func__);
}

module_init(sample_init);
module_exit(sample_exit);
MODULE_LICENSE("GPL");
