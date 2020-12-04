$(function(){ //DOM Ready

    function navigate(url)
    {
        window.location.href = url;
    }

    $(document).attr("title", "Control Panel");
    content_width = (1 + 0) * 1024 + 0
    $('.gridster').width(content_width)
    $(".gridster ul").gridster({
        widget_margins: [0, 0],
        widget_base_dimensions: [1, 1],
        avoid_overlapped_widgets: true,
        max_rows: 15,
        max_size_x: 1024,
        shift_widgets_up: false
    }).data('gridster').disable();

    // Add Widgets

    var gridster = $(".gridster ul").gridster().data('gridster');
    
        gridster.add_widget('<li><div data-bind="attr: {style: widget_style}" class="widget widget-basedisplay-default-header" id="default-header"><h1 class="title" data-bind="text: title, attr:{ style: title_style}"></h1><h1 class="title2" data-bind="text: title2, attr:{ style: title2_style}"></h1><div class="valueunit" data-bind="attr:{ style: container_style}"><h2 class="value" data-bind="html: value, attr:{ style: value_style}"></h2><p class="unit" data-bind="html: unit, attr:{ style: unit_style}"></p></div><h1 class="state_text" data-bind="text: state_text, attr: {style: state_text_style}"></h1></div></li>', 744, 40, 21, 1)
    
        gridster.add_widget('<li><div data-bind="attr: {style: widget_style}" class="widget widget-baseclock-default-clock-clock" id="default-clock-clock"><h1 class="date"data-bind="text: date, attr: {style: date_style}"></h1><h2 class="time" data-bind="text: time, attr: {style: time_style}"></h2></div></li>', 240, 40, 765, 1)
    
        gridster.add_widget('<li><div data-bind="attr: {style: widget_style}" class="widget widget-baseswitch-default-led" id="default-led"><span class="toggle-area" id="switch"></span><h1 class="title" data-bind="text: title, attr:{style: title_style}"></h1><h1 class="title2" data-bind="text: title2, attr:{style: title2_style}"></h1><h2 class="icon" data-bind="attr:{style: icon_style}"><i data-bind="attr: {class: icon}"></i></h2><h1 class="state_text" data-bind="text: state_text, attr: {style: state_text_style}"></h1></div></li>', 120, 120, 21, 122)
    
        gridster.add_widget('<li><div data-bind="attr: {style: widget_style}" class="widget widget-baseswitch-default-usb-led" id="default-usb-led"><span class="toggle-area" id="switch"></span><h1 class="title" data-bind="text: title, attr:{style: title_style}"></h1><h1 class="title2" data-bind="text: title2, attr:{style: title2_style}"></h1><h2 class="icon" data-bind="attr:{style: icon_style}"><i data-bind="attr: {class: icon}"></i></h2><h1 class="state_text" data-bind="text: state_text, attr: {style: state_text_style}"></h1></div></li>', 120, 120, 161, 122)
    
        gridster.add_widget('<li><div data-bind="attr: {style: widget_style}" class="widget widget-baseswitch-default-rasbian-display" id="default-rasbian-display"><span class="toggle-area" id="switch"></span><h1 class="title" data-bind="text: title, attr:{style: title_style}"></h1><h1 class="title2" data-bind="text: title2, attr:{style: title2_style}"></h1><h2 class="icon" data-bind="attr:{style: icon_style}"><i data-bind="attr: {class: icon}"></i></h2><h1 class="state_text" data-bind="text: state_text, attr: {style: state_text_style}"></h1></div></li>', 120, 120, 301, 122)
    
        gridster.add_widget('<li><div data-bind="attr: {style: widget_style}" class="widget widget-basedisplay-default-light-intensity" id="default-light-intensity"><h1 class="title" data-bind="text: title, attr:{ style: title_style}"></h1><h1 class="title2" data-bind="text: title2, attr:{ style: title2_style}"></h1><div class="valueunit" data-bind="attr:{ style: container_style}"><h2 class="value" data-bind="html: value, attr:{ style: value_style}"></h2><p class="unit" data-bind="html: unit, attr:{ style: unit_style}"></p></div><h1 class="state_text" data-bind="text: state_text, attr: {style: state_text_style}"></h1></div></li>', 120, 120, 21, 263)
    
        gridster.add_widget('<li><div data-bind="attr: {style: widget_style}" class="widget widget-basedisplay-default-temperature" id="default-temperature"><h1 class="title" data-bind="text: title, attr:{ style: title_style}"></h1><h1 class="title2" data-bind="text: title2, attr:{ style: title2_style}"></h1><div class="valueunit" data-bind="attr:{ style: container_style}"><h2 class="value" data-bind="html: value, attr:{ style: value_style}"></h2><p class="unit" data-bind="html: unit, attr:{ style: unit_style}"></p></div><h1 class="state_text" data-bind="text: state_text, attr: {style: state_text_style}"></h1></div></li>', 120, 120, 161, 263)
    
        gridster.add_widget('<li><div data-bind="attr: {style: widget_style}" class="widget widget-basedisplay-default-humidity" id="default-humidity"><h1 class="title" data-bind="text: title, attr:{ style: title_style}"></h1><h1 class="title2" data-bind="text: title2, attr:{ style: title2_style}"></h1><div class="valueunit" data-bind="attr:{ style: container_style}"><h2 class="value" data-bind="html: value, attr:{ style: value_style}"></h2><p class="unit" data-bind="html: unit, attr:{ style: unit_style}"></p></div><h1 class="state_text" data-bind="text: state_text, attr: {style: state_text_style}"></h1></div></li>', 120, 120, 301, 263)
    
        gridster.add_widget('<li><div data-bind="attr: {style: widget_style}" class="widget widget-basedisplay-default-btiphone" id="default-btiphone"><h1 class="title" data-bind="text: title, attr:{ style: title_style}"></h1><h1 class="title2" data-bind="text: title2, attr:{ style: title2_style}"></h1><div class="valueunit" data-bind="attr:{ style: container_style}"><h2 class="value" data-bind="html: value, attr:{ style: value_style}"></h2><p class="unit" data-bind="html: unit, attr:{ style: unit_style}"></p></div><h1 class="state_text" data-bind="text: state_text, attr: {style: state_text_style}"></h1></div></li>', 120, 120, 21, 404)
    
        gridster.add_widget('<li><div data-bind="attr: {style: widget_style}" class="widget widget-basejavascript-default-reload" id="default-reload"><span class="toggle-area" id="switch"></span><h1 class="title" data-bind="text: title, attr:{style: title_style}"></h1><h1 class="title2" data-bind="text: title2, attr:{style: title2_style}"></h1><h2 class="icon" data-bind="attr:{style: icon_style}"><i data-bind="attr: {class: icon}"></i></h2></div></li>', 1024, 60, 1, 541)
    


    var widgets = {}
    // Initialize Widgets
    
        widgets["default-header"] = new basedisplay("default-header", "", "dark1", {'widget_type': 'basedisplay', 'fields': {'title': '', 'title2': 'IoT 2 Contorl Appdaemon', 'value': '', 'unit': '', 'state_text': ''}, 'static_css': {'title_style': 'color: #fff;font-size: 150%;height: 0px;', 'title2_style': 'color: #fff;font-size: 150%;text-align: left;vertical-align: top;top: 6px;', 'unit_style': '', 'value_style': 'color: #fff;font-size: 150%;', 'state_text_style': '', 'widget_style': 'background-color: transparent;', 'container_style': ''}, 'css': {}, 'icons': [], 'static_icons': [], 'title2_style': 'text-align: left;vertical-align: top;font-size: 150%;color: #fff;top: 6px;', 'use_comma': 0, 'precision': 1, 'use_hass_icon': 1, 'namespace': 'default'})
    
        widgets["default-clock-clock"] = new baseclock("default-clock-clock", "", "dark1", {'widget_type': 'baseclock', 'fields': {'date': '', 'time': ''}, 'static_css': {'date_style': 'visibility: hidden;height: 0px;', 'time_style': 'color: #fff;font-size: 150%;', 'widget_style': 'background-color: transparent;'}, 'static_icons': [], 'icons': [], 'css': {}, 'entity': 'clock.clock', 'title_is_friendly_name': 1, 'use_comma': 0, 'precision': 1, 'use_hass_icon': 1, 'namespace': 'default'})
    
        widgets["default-led"] = new baseswitch("default-led", "", "dark1", {'widget_type': 'baseswitch', 'entity': 'switch.led', 'state_active': 'on', 'state_inactive': 'off', 'enable': 1, 'post_service_active': {'service': 'homeassistant/turn_on', 'entity_id': 'switch.led'}, 'post_service_inactive': {'service': 'homeassistant/turn_off', 'entity_id': 'switch.led'}, 'fields': {'title': 'LED', 'title2': '', 'icon': '', 'icon_style': '', 'state_text': ''}, 'icons': {'icon_on': 'mdi-led-on', 'icon_off': 'mdi-led-off'}, 'static_icons': [], 'css': {'icon_style_active': 'color: #3a53b7;', 'icon_style_inactive': 'color: antiquewhite;'}, 'static_css': {'title_style': 'color: #646464;font-weight: 400;', 'title2_style': 'color: #646464;font-weight: 400;', 'state_text_style': 'color: #646464;', 'widget_style': 'background-color: rgba(0, 0, 0, 0.5);box-shadow: 0 45px 100px rgba(0, 0, 0, 0.4);'}, 'icon_on': 'mdi-led-on', 'icon_off': 'mdi-led-off', 'use_comma': 0, 'precision': 1, 'use_hass_icon': 1, 'namespace': 'default'})
    
        widgets["default-usb-led"] = new baseswitch("default-usb-led", "", "dark1", {'widget_type': 'baseswitch', 'entity': 'switch.usb_led', 'state_active': 'on', 'state_inactive': 'off', 'enable': 1, 'post_service_active': {'service': 'homeassistant/turn_on', 'entity_id': 'switch.usb_led'}, 'post_service_inactive': {'service': 'homeassistant/turn_off', 'entity_id': 'switch.usb_led'}, 'fields': {'title': 'USB LED', 'title2': '', 'icon': '', 'icon_style': '', 'state_text': ''}, 'icons': {'icon_on': 'mdi-alarm-light', 'icon_off': 'mdi-alarm-light-outline'}, 'static_icons': [], 'css': {'icon_style_active': 'color: #3a53b7;', 'icon_style_inactive': 'color: antiquewhite;'}, 'static_css': {'title_style': 'color: #646464;font-weight: 400;', 'title2_style': 'color: #646464;font-weight: 400;', 'state_text_style': 'color: #646464;', 'widget_style': 'background-color: rgba(0, 0, 0, 0.5);box-shadow: 0 45px 100px rgba(0, 0, 0, 0.4);'}, 'icon_on': 'mdi-alarm-light', 'icon_off': 'mdi-alarm-light-outline', 'use_comma': 0, 'precision': 1, 'use_hass_icon': 1, 'namespace': 'default'})
    
        widgets["default-rasbian-display"] = new baseswitch("default-rasbian-display", "", "dark1", {'widget_type': 'baseswitch', 'entity': 'switch.rasbian_display', 'state_active': 'on', 'state_inactive': 'off', 'enable': 1, 'post_service_active': {'service': 'homeassistant/turn_on', 'entity_id': 'switch.rasbian_display'}, 'post_service_inactive': {'service': 'homeassistant/turn_off', 'entity_id': 'switch.rasbian_display'}, 'fields': {'title': 'Rasbian Display', 'title2': '', 'icon': '', 'icon_style': '', 'state_text': ''}, 'icons': {'icon_on': 'mdi-monitor', 'icon_off': 'mdi-monitor'}, 'static_icons': [], 'css': {'icon_style_active': 'color: #3a53b7;', 'icon_style_inactive': 'color: antiquewhite;'}, 'static_css': {'title_style': 'color: #646464;font-weight: 400;', 'title2_style': 'color: #646464;font-weight: 400;', 'state_text_style': 'color: #646464;', 'widget_style': 'background-color: rgba(0, 0, 0, 0.5);box-shadow: 0 45px 100px rgba(0, 0, 0, 0.4);'}, 'icon_on': 'mdi-monitor', 'icon_off': 'mdi-monitor', 'use_comma': 0, 'precision': 1, 'use_hass_icon': 1, 'namespace': 'default'})
    
        widgets["default-light-intensity"] = new basedisplay("default-light-intensity", "", "dark1", {'widget_type': 'basedisplay', 'entity': 'sensor.light_intensity', 'entity_to_sub_entity_attribute': '', 'sub_entity': '', 'sub_entity_to_entity_attribute': '', 'fields': {'title': 'Light Intensity', 'title2': '', 'value': '', 'unit': '', 'state_text': ''}, 'static_css': {'title_style': 'color: #646464;font-weight: 400;', 'title2_style': 'color: #646464;font-weight: 400;', 'state_text_style': '', 'widget_style': 'background-color: rgba(0, 0, 0, 0.5);box-shadow: 0 45px 100px rgba(0, 0, 0, 0.4);', 'container_style': ''}, 'css': {'value_style': '', 'text_style': 'color: #646464;', 'unit_style': ''}, 'icons': [], 'static_icons': [], 'precision': 0, 'use_comma': 0, 'use_hass_icon': 1, 'namespace': 'default'})
    
        widgets["default-temperature"] = new basedisplay("default-temperature", "", "dark1", {'widget_type': 'basedisplay', 'entity': 'sensor.temperature', 'entity_to_sub_entity_attribute': '', 'sub_entity': '', 'sub_entity_to_entity_attribute': '', 'fields': {'title': 'Temperature', 'title2': '', 'value': '', 'unit': '', 'state_text': ''}, 'static_css': {'title_style': 'color: #646464;font-weight: 400;', 'title2_style': 'color: #646464;font-weight: 400;', 'state_text_style': '', 'widget_style': 'background-color: rgba(0, 0, 0, 0.5);box-shadow: 0 45px 100px rgba(0, 0, 0, 0.4);', 'container_style': ''}, 'css': {'value_style': '', 'text_style': 'color: #646464;', 'unit_style': ''}, 'icons': [], 'static_icons': [], 'units': '&deg;C', 'precision': 1, 'use_comma': 0, 'use_hass_icon': 1, 'namespace': 'default'})
    
        widgets["default-humidity"] = new basedisplay("default-humidity", "", "dark1", {'widget_type': 'basedisplay', 'entity': 'sensor.humidity', 'entity_to_sub_entity_attribute': '', 'sub_entity': '', 'sub_entity_to_entity_attribute': '', 'fields': {'title': 'Humidity', 'title2': '', 'value': '', 'unit': '', 'state_text': ''}, 'static_css': {'title_style': 'color: #646464;font-weight: 400;', 'title2_style': 'color: #646464;font-weight: 400;', 'state_text_style': '', 'widget_style': 'background-color: rgba(0, 0, 0, 0.5);box-shadow: 0 45px 100px rgba(0, 0, 0, 0.4);', 'container_style': ''}, 'css': {'value_style': '', 'text_style': 'color: #646464;', 'unit_style': ''}, 'icons': [], 'static_icons': [], 'units': '%', 'precision': 1, 'use_comma': 0, 'use_hass_icon': 1, 'namespace': 'default'})
    
        widgets["default-btiphone"] = new basedisplay("default-btiphone", "", "dark1", {'widget_type': 'basedisplay', 'entity': 'sensor.kyu_iphone', 'entity_to_sub_entity_attribute': '', 'sub_entity': '', 'sub_entity_to_entity_attribute': '', 'fields': {'title': 'Kyu iPhone Confidence', 'title2': '', 'value': '', 'unit': '', 'state_text': ''}, 'static_css': {'title_style': 'color: #646464;font-weight: 400;', 'title2_style': 'color: #646464;font-weight: 400;', 'state_text_style': '', 'widget_style': 'background-color: rgba(0, 0, 0, 0.5);box-shadow: 0 45px 100px rgba(0, 0, 0, 0.4);', 'container_style': ''}, 'css': {'value_style': '', 'text_style': 'color: #646464;', 'unit_style': ''}, 'icons': [], 'static_icons': [], 'units': '%', 'precision': 0, 'use_comma': 0, 'use_hass_icon': 1, 'namespace': 'default'})
    
        widgets["default-reload"] = new basejavascript("default-reload", "", "dark1", {'widget_type': 'basejavascript', 'command': 'location.reload(true)', 'fields': {'title': '', 'title2': '', 'icon': '', 'icon_style': ''}, 'icons': {'icon_active': 'fa-spinner fa-spin', 'icon_inactive': 'fa-refresh'}, 'static_css': {'title_style': 'color: #646464;font-weight: 400;', 'title2_style': 'color: #646464;font-weight: 400;', 'widget_style': 'background-color: rgba(0, 0, 0, 0.5);box-shadow: 0 45px 100px rgba(0, 0, 0, 0.4);'}, 'css': {'icon_active_style': 'color: #646464;top: 6px;', 'icon_inactive_style': 'color: #646464;top: 6px;'}, 'static_icons': [], 'icon_active_style': 'top: 6px;', 'icon_inactive_style': 'top: 6px;', 'use_comma': 0, 'precision': 1, 'use_hass_icon': 1, 'namespace': 'default'})
    

    // Setup click handler to cancel timeout navigations

    $( ".gridster" ).click(function(){
        clearTimeout(myTimeout);
        if (myTimeoutSticky) {
            myTimeout = setTimeout(function() { navigate(myTimeoutUrl); }, myTimeoutDelay);
        }
    });

    // Set up timeout

    var myTimeout;
    var myTimeoutUrl;
    var myTimeoutDelay;
    var myTimeoutSticky = 0;

    if (location.search != "")
    {
        var query = location.search.substr(1);
        var result = {};
        query.split("&").forEach(function(part) {
        var item = part.split("=");
        result[item[0]] = decodeURIComponent(item[1]);
        });

        if ("timeout" in result && "return" in result)
        {
            url = result.return
            argcount = 0
            for (arg in result)
            {
                if (arg != "timeout" && arg != "return" && arg != "sticky")
                {
                    if (argcount == 0)
                    {
                        url += "?";
                    }
                    else
                    {
                        url += "?";
                    }
                    argcount ++;
                    url += arg + "=" + result[arg]
                }
            }
            if ("sticky" in result)
            {
                myTimeoutSticky = (result.sticky == "1");
            }
            myTimeoutUrl = url;
            myTimeoutDelay = result.timeout * 1000;
            myTimeout = setTimeout(function() { navigate(url); }, result.timeout * 1000);
        }
    }

    // Start listening for AD Events

    window.dashstream = new DashStream("ws", location.protocol, document.domain, location.port, "Control Panel", widgets);

});