/*
 * Copyright (C) 2008 Google, Inc.
 * Copyright (C) 2010-2014, The Linux Foundation. All rights reserved.
 * Author: Nick Pelly <npelly@google.com>
 *
 * This software is licensed under the terms of the GNU General Public
 * License version 2, as published by the Free Software Foundation, and
 * may be copied, distributed, and modified under those terms.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 */

#ifndef __ASM_ARCH_MSM_SERIAL_HS_H
#define __ASM_ARCH_MSM_SERIAL_HS_H

#include <linux/serial_core.h>

/**
 * struct msm_serial_hs_platform_data - platform device data
 *					for msm hsuart device
 * @wakeup_irq : IRQ line to be configured as Wakeup source.
 * @inject_rx_on_wakeup : Set 1 if specific character to be inserted on wakeup
 * @rx_to_inject : Character to be inserted on wakeup
 * @gpio_config : Configure gpios that are used for uart communication
 * @userid : User-defined number to be used to enumerate device as tty<userid>
 * @uart_tx_gpio: GPIO number for UART Tx Line.
 * @uart_rx_gpio: GPIO number for UART Rx Line.
 * @uart_cts_gpio: GPIO number for UART CTS Line.
 * @uart_rfr_gpio: GPIO number for UART RFR Line.
 * @bam_tx_ep_pipe_index : BAM TX Endpoint Pipe Index for HSUART
 * @bam_tx_ep_pipe_index : BAM RX Endpoint Pipe Index for HSUART
 * @no_suspend_delay : Flag used to make system go to suspend
 * immediately or not
 * @obs: Flag to enable out of band sleep feature support
 */
struct msm_serial_hs_platform_data {
	int wakeup_irq;  /* wakeup irq */
	bool inject_rx_on_wakeup;
	u8 rx_to_inject;
	int (*gpio_config)(int);
	int userid;

	int uart_tx_gpio;
	int uart_rx_gpio;
	int uart_cts_gpio;
	int uart_rfr_gpio;
	unsigned bam_tx_ep_pipe_index;
	unsigned bam_rx_ep_pipe_index;
	bool no_suspend_delay;
	bool obs;
};

typedef void (*wake_peer_fn)(struct uart_port *);

/* return true when tx is empty */
unsigned int msm_hs_tx_empty(struct uart_port *uport);
void msm_hs_request_clock_off(struct uart_port *uport);
void msm_hs_request_clock_on(struct uart_port *uport);
struct uart_port *msm_hs_get_uart_port(int port_index);
void msm_hs_set_mctrl(struct uart_port *uport,
				    unsigned int mctrl);
void msm_hs_set_clock(int port_index, int on);
//[P1_BRINGUP_S]
//BT_S : [CONBT-966] Fix to Bluetooth sleep & uart driver
#if defined(CONFIG_LGE_BLUESLEEP) || defined(CONFIG_LGE_BLUETOOTH_PM)
#define CLOCK_REQUEST_AVAILABLE 	0
#define CLOCK_REQUEST_UNAVAILABLE 	1
struct uart_port * msm_hs_get_bt_uport(unsigned int line);
#endif /* defined(CONFIG_LGE_BLUESLEEP) || defined(CONFIG_LGE_BLUETOOTH_PM) */
//BT_E : [CONBT-966] Fix to Bluetooth sleep & uart driver
//BT_S : [CONBT-966] Fix to HCI command timeout
int msm_hs_get_pm_state_active(struct uart_port *uport);
//BT_E : [CONBT-966] Fix to HCI command timeout
//[P1_BRINGUP_E]
void msm_hs_set_wake_peer(struct uart_port *uport, wake_peer_fn wake_peer);
#endif
