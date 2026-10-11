#pragma once
#define LGFX_USE_V1
#include <LovyanGFX.hpp>

class LGFX : public lgfx::LGFX_Device {
    lgfx::Panel_ST7796 _panel;
    lgfx::Bus_SPI _bus;
    lgfx::Light_PWM _light;

    public:
       LGFX() {
        {
            auto cfg = _bus.config();
            cfg.spi_host   = SPI2_HOST;
            cfg.spi_mode   = 0;
            cfg.freq_write = 20000000;
            cfg.freq_read  = 16000000;
            cfg.pin_sclk   = 7;
            cfg.pin_mosi   = 9;
            cfg.pin_miso   = 8;
            cfg.pin_dc     = 2;
            _bus.config(cfg);
            _panel.setBus(&_bus);
        }
        {
            auto cfg = _panel.config();
            cfg.pin_cs       = 1;
            cfg.pin_rst      = 3;
            cfg.pin_busy     = -1;
            cfg.panel_width  = 320;
            cfg.panel_height = 480;
            cfg.readable     = false;
            cfg.invert       = false;
            cfg.rgb_order    = false;
            cfg.bus_shared   = false;
            _panel.config(cfg);
        }
        {
            auto cfg = _light.config();
            cfg.pin_bl      = 4;
            cfg.invert      = false;
            cfg.freq        = 44100;
            cfg.pwm_channel = 7;
            _light.config(cfg);
            _panel.setLight(&_light);
        }
        setPanel(&_panel);
    }
};