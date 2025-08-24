/**
 * @file    button.c
 * @author  Onur
 * @date    2025-07-04
 * @brief   Source file for button interface.
 *
 * This file implements the polling mechanism and internal state tracking
 * logic for handling button press and release events. It abstracts GPIO
 * hardware access via a HAL layer and enables user-defined callbacks.
 * 
 */

#include "button.h"
#include "hal_gpio.h"

/*-----------------------------------------------------------------------------
 *                       PUBLIC FUNCTION DEFINITIONS
 *---------------------------------------------------------------------------*/

bool button_init(button_handle_t *handle, const button_config_t *config)
{
    if ((handle == NULL) || (config == NULL))
    {
        return false;
    }

    handle->config = *config;
    handle->last_state = BUTTON_STATE_RELEASED;
    handle->is_initialized = false;

    if (!hal_gpio_config_input(config->gpio_pin))
    {
        return false;
    }

    handle->is_initialized = true;
    return true;
}

button_state_e button_read(const button_handle_t *handle)
{
    if ((handle == NULL) || (handle->is_initialized == false))
    {
        return BUTTON_STATE_RELEASED;
    }

    bool level = hal_gpio_read(handle->config.gpio_pin);

    if (handle->config.active_low)
    {
        return (level == false) ? BUTTON_STATE_PRESSED : BUTTON_STATE_RELEASED;
    }
    else
    {
        return (level == true) ? BUTTON_STATE_PRESSED : BUTTON_STATE_RELEASED;
    }
}

void button_task(button_handle_t *handle)
{
    if ((handle == NULL) || (handle->is_initialized == false))
    {
        return;
    }

    button_state_e current_state = button_read(handle);

    if (current_state != handle->last_state)
    {
        handle->last_state = current_state;

        if (handle->config.callback != NULL)
        {
            if (current_state == BUTTON_STATE_PRESSED)
            {
                handle->config.callback(BUTTON_EVENT_PRESSED);
            }
            else
            {
                handle->config.callback(BUTTON_EVENT_RELEASED);
            }
        }
    }
}

// End of file
