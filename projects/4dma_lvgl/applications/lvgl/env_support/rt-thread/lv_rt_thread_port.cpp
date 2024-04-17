/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: MIT
 *
 * Change Logs:
 * Date           Author       Notes
 * 2021-10-18     Meco Man     the first version
 * 2022-05-10     Meco Man     improve rt-thread initialization process
 */

#ifdef __RTTHREAD__

#include <lvgl.h>
#include <rtthread.h>
#include <lv_demo_stress.h>
#include <tft.h>
extern TFT tft;

#define DBG_TAG "LVGL"
#define DBG_LVL DBG_INFO
#include <rtdbg.h>

#ifndef PKG_LVGL_THREAD_STACK_SIZE
#define PKG_LVGL_THREAD_STACK_SIZE 4096
#endif /* PKG_LVGL_THREAD_STACK_SIZE */

#ifndef PKG_LVGL_THREAD_PRIO
#define PKG_LVGL_THREAD_PRIO (RT_THREAD_PRIORITY_MAX * 2 / 3)
#endif /* PKG_LVGL_THREAD_PRIO */

extern void lv_port_disp_init(void);
extern void lv_port_indev_init(void);
extern void lv_user_gui_init(void);
extern void lv_demo_stress();
extern void lv_demo_benchmark();

static struct rt_thread lvgl_thread;

#ifdef rt_align
rt_align(RT_ALIGN_SIZE)
#else
ALIGN(RT_ALIGN_SIZE)
#endif
    static rt_uint8_t lvgl_thread_stack[PKG_LVGL_THREAD_STACK_SIZE];

#if LV_USE_LOG
static void lv_rt_log(const char *buf)
{
    LOG_I(buf);
}
#endif /* LV_USE_LOG */

static void lvgl_thread_entry(void *parameter)
{

    tft.begin("r61581");
#if LV_USE_LOG
    lv_log_register_print_cb(lv_rt_log);
#endif /* LV_USE_LOG */
    lv_init();
    lv_port_disp_init();
    lv_demo_stress();

    // lv_obj_t *cont = lv_obj_create(lv_scr_act());
    // lv_obj_t *label = lv_label_create(cont);
    // lv_label_set_text(label, "Helllllo, world!");
    // lv_obj_set_size(cont, 160, 50);
    // lv_obj_center(cont);
    // lv_obj_center(label);

    // lv_port_indev_init();
    // lv_user_gui_init();

    /* handle the tasks of LVGL */
    while (1)
    {
        lv_task_handler();
        rt_thread_mdelay(LV_DISP_DEF_REFR_PERIOD);
    }
}

static int lvgl_thread_init(void)
{
    rt_err_t err;

    err = rt_thread_init(&lvgl_thread, "LVGL", lvgl_thread_entry, RT_NULL,
                         &lvgl_thread_stack[0], sizeof(lvgl_thread_stack), PKG_LVGL_THREAD_PRIO, 10);
    if (err != RT_EOK)
    {
        LOG_E("Failed to create LVGL thread");
        return -1;
    }
    rt_thread_startup(&lvgl_thread);

    return 0;
}
INIT_ENV_EXPORT(lvgl_thread_init);

#endif /*__RTTHREAD__*/
