$(function(){ //DOM Ready

    function navigate(url)
    {
        window.location.href = url;
    }

    $(document).attr("title", "Main");
    content_width = (170 + 15) * 11 + 15
    $('.gridster').width(content_width)
    $(".gridster ul").gridster({
        widget_margins: [15, 15],
        widget_base_dimensions: [170, 180],
        avoid_overlapped_widgets: true,
        max_rows: 15,
        max_size_x: 11,
        shift_widgets_up: false
    }).data('gridster').disable();

    // Add Widgets

    var gridster = $(".gridster ul").gridster().data('gridster');
    
        gridster.add_widget('<li><div data-bind="attr: {style: widget_style}" class="widget widget-baseclock-default-clock" id="default-clock"><h1 class="date"data-bind="text: date, attr: {style: date_style}"></h1><h2 class="time" data-bind="text: time, attr: {style: time_style}"></h2></div></li>', 4, 2, 1, 1)
    
        gridster.add_widget('<li><div data-bind="attr: {style: widget_style}" class="widget widget-baseswitch-default-led" id="default-led"><span class="toggle-area" id="switch"></span><h1 class="title" data-bind="text: title, attr:{style: title_style}"></h1><h1 class="title2" data-bind="text: title2, attr:{style: title2_style}"></h1><h2 class="icon" data-bind="attr:{style: icon_style}"><i data-bind="attr: {class: icon}"></i></h2><h1 class="state_text" data-bind="text: state_text, attr: {style: state_text_style}"></h1></div></li>', 1, 1, 5, 2)
    
        gridster.add_widget('<li><div data-bind="attr: {style: widget_style}" class="widget widget-baseswitch-default-usb-led" id="default-usb-led"><span class="toggle-area" id="switch"></span><h1 class="title" data-bind="text: title, attr:{style: title_style}"></h1><h1 class="title2" data-bind="text: title2, attr:{style: title2_style}"></h1><h2 class="icon" data-bind="attr:{style: icon_style}"><i data-bind="attr: {class: icon}"></i></h2><h1 class="state_text" data-bind="text: state_text, attr: {style: state_text_style}"></h1></div></li>', 1, 1, 6, 2)
    
        gridster.add_widget('<li><div data-bind="attr: {style: widget_style}" class="widget widget-baseswitch-default-rasbian-display" id="default-rasbian-display"><span class="toggle-area" id="switch"></span><h1 class="title" data-bind="text: title, attr:{style: title_style}"></h1><h1 class="title2" data-bind="text: title2, attr:{style: title2_style}"></h1><h2 class="icon" data-bind="attr:{style: icon_style}"><i data-bind="attr: {class: icon}"></i></h2><h1 class="state_text" data-bind="text: state_text, attr: {style: state_text_style}"></h1></div></li>', 1, 1, 7, 2)
    
        gridster.add_widget('<li><div data-bind="attr: {style: widget_style}" class="widget widget-basedisplay-default-light-intensity" id="default-light-intensity"><h1 class="title" data-bind="text: title, attr:{ style: title_style}"></h1><h1 class="title2" data-bind="text: title2, attr:{ style: title2_style}"></h1><div class="valueunit" data-bind="attr:{ style: container_style}"><h2 class="value" data-bind="html: value, attr:{ style: value_style}"></h2><p class="unit" data-bind="html: unit, attr:{ style: unit_style}"></p></div><h1 class="state_text" data-bind="text: state_text, attr: {style: state_text_style}"></h1></div></li>', 1, 1, 1, 3)
    
        gridster.add_widget('<li><div data-bind="attr: {style: widget_style}" class="widget widget-basedisplay-default-temperature" id="default-temperature"><h1 class="title" data-bind="text: title, attr:{ style: title_style}"></h1><h1 class="title2" data-bind="text: title2, attr:{ style: title2_style}"></h1><div class="valueunit" data-bind="attr:{ style: container_style}"><h2 class="value" data-bind="html: value, attr:{ style: value_style}"></h2><p class="unit" data-bind="html: unit, attr:{ style: unit_style}"></p></div><h1 class="state_text" data-bind="text: state_text, attr: {style: state_text_style}"></h1></div></li>', 1, 1, 2, 3)
    
        gridster.add_widget('<li><div data-bind="attr: {style: widget_style}" class="widget widget-basedisplay-default-humidity" id="default-humidity"><h1 class="title" data-bind="text: title, attr:{ style: title_style}"></h1><h1 class="title2" data-bind="text: title2, attr:{ style: title2_style}"></h1><div class="valueunit" data-bind="attr:{ style: container_style}"><h2 class="value" data-bind="html: value, attr:{ style: value_style}"></h2><p class="unit" data-bind="html: unit, attr:{ style: unit_style}"></p></div><h1 class="state_text" data-bind="text: state_text, attr: {style: state_text_style}"></h1></div></li>', 1, 1, 3, 3)
    
        gridster.add_widget('<li><div data-bind="attr: {style: widget_style}" class="widget widget-basedisplay-default-btiphone" id="default-btiphone"><h1 class="title" data-bind="text: title, attr:{ style: title_style}"></h1><h1 class="title2" data-bind="text: title2, attr:{ style: title2_style}"></h1><div class="valueunit" data-bind="attr:{ style: container_style}"><h2 class="value" data-bind="html: value, attr:{ style: value_style}"></h2><p class="unit" data-bind="html: unit, attr:{ style: unit_style}"></p></div><h1 class="state_text" data-bind="text: state_text, attr: {style: state_text_style}"></h1></div></li>', 1, 1, 1, 4)
    
        gridster.add_widget('<li><div data-bind="attr: {style: widget_style}" class="widget widget-basejavascript-default-reload" id="default-reload"><span class="toggle-area" id="switch"></span><h1 class="title" data-bind="text: title, attr:{style: title_style}"></h1><h1 class="title2" data-bind="text: title2, attr:{style: title2_style}"></h1><h2 class="icon" data-bind="attr:{style: icon_style}"><i data-bind="attr: {class: icon}"></i></h2></div></li>', 1, 1, 1, 5)
    


    var widgets = {}
    // Initialize Widgets
    
        widgets["default-clock"] = new baseclock("default-clock", "", "zen", {'widget_type': 'baseclock', 'fields': {'date': '', 'time': ''}, 'static_css': {'date_style': 'color: #fff;', 'time_style': 'font-weight: bold;color: white;text-shadow: 0 1px 0 #ccc, 0 2px 0 #c9c9c9, 0 3px 0 #bbb, 0 4px 0 #b9b9b9, 0 4px 0 #aaa, 0 6px 1px rgba(0,0,0,.1), 0 0 5px rgba(0,0,0,.1), 0 1px 3px rgba(0,0,0,.3), 0 3px 4px rgba(0,0,0,.2), 0 5px 10px rgba(0,0,0,.25), 0 10px 10px rgba(0,0,0,.2), 0 20px 20px rgba(0,0,0,.15);', 'widget_style': 'background-color: rgba(0,0,0,0.25);'}, 'static_icons': [], 'icons': [], 'css': {}, 'namespace': 'default'})
    
        widgets["default-led"] = new baseswitch("default-led", "", "zen", {'widget_type': 'baseswitch', 'entity': 'switch.led', 'state_active': 'on', 'state_inactive': 'off', 'enable': 1, 'post_service_active': {'service': 'homeassistant/turn_on', 'entity_id': 'switch.led'}, 'post_service_inactive': {'service': 'homeassistant/turn_off', 'entity_id': 'switch.led'}, 'fields': {'title': 'LED', 'title2': '', 'icon': '', 'icon_style': '', 'state_text': ''}, 'icons': {'icon_on': 'mdi-led-on', 'icon_off': 'mdi-led-off'}, 'static_icons': [], 'css': {'icon_style_active': 'color: #ff0055;', 'icon_style_inactive': 'color: rgba(0,0,0,0.5);'}, 'static_css': {'title_style': 'color: #000;font-weight: bold;', 'title2_style': 'color: #000;', 'state_text_style': 'color: #ff0055;font-weight: bold;', 'widget_style': 'background-image: url(css/zen/img/zen_bg2.jpg);'}, 'icon_on': 'mdi-led-on', 'icon_off': 'mdi-led-off', 'namespace': 'default'})
    
        widgets["default-usb-led"] = new baseswitch("default-usb-led", "", "zen", {'widget_type': 'baseswitch', 'entity': 'switch.usb_led', 'state_active': 'on', 'state_inactive': 'off', 'enable': 1, 'post_service_active': {'service': 'homeassistant/turn_on', 'entity_id': 'switch.usb_led'}, 'post_service_inactive': {'service': 'homeassistant/turn_off', 'entity_id': 'switch.usb_led'}, 'fields': {'title': 'USB LED', 'title2': '', 'icon': '', 'icon_style': '', 'state_text': ''}, 'icons': {'icon_on': 'mdi-alarm-light', 'icon_off': 'mdi-alarm-light-outline'}, 'static_icons': [], 'css': {'icon_style_active': 'color: #ff0055;', 'icon_style_inactive': 'color: rgba(0,0,0,0.5);'}, 'static_css': {'title_style': 'color: #000;font-weight: bold;', 'title2_style': 'color: #000;', 'state_text_style': 'color: #ff0055;font-weight: bold;', 'widget_style': 'background-image: url(css/zen/img/zen_bg2.jpg);'}, 'icon_on': 'mdi-alarm-light', 'icon_off': 'mdi-alarm-light-outline', 'namespace': 'default'})
    
        widgets["default-rasbian-display"] = new baseswitch("default-rasbian-display", "", "zen", {'widget_type': 'baseswitch', 'entity': 'switch.rasbian_display', 'state_active': 'on', 'state_inactive': 'off', 'enable': 1, 'post_service_active': {'service': 'homeassistant/turn_on', 'entity_id': 'switch.rasbian_display'}, 'post_service_inactive': {'service': 'homeassistant/turn_off', 'entity_id': 'switch.rasbian_display'}, 'fields': {'title': 'Rasbian Display', 'title2': '', 'icon': '', 'icon_style': '', 'state_text': ''}, 'icons': {'icon_on': 'mdi-monitor', 'icon_off': 'mdi-monitor'}, 'static_icons': [], 'css': {'icon_style_active': 'color: #ff0055;', 'icon_style_inactive': 'color: rgba(0,0,0,0.5);'}, 'static_css': {'title_style': 'color: #000;font-weight: bold;', 'title2_style': 'color: #000;', 'state_text_style': 'color: #ff0055;font-weight: bold;', 'widget_style': 'background-image: url(css/zen/img/zen_bg2.jpg);'}, 'icon_on': 'mdi-monitor', 'icon_off': 'mdi-monitor', 'namespace': 'default'})
    
        widgets["default-light-intensity"] = new basedisplay("default-light-intensity", "", "zen", {'widget_type': 'basedisplay', 'entity': 'sensor.light_intensity', 'entity_to_sub_entity_attribute': '', 'sub_entity': '', 'sub_entity_to_entity_attribute': '', 'fields': {'title': 'Light Intensity', 'title2': '', 'value': '', 'unit': '', 'state_text': ''}, 'static_css': {'title_style': 'color: #000;font-weight: bold;', 'title2_style': 'color: #000;', 'state_text_style': 'color: #ff0055;font-size: 100%;', 'widget_style': 'background-image: url(css/zen/img/zen_bg2.jpg);', 'container_style': ''}, 'css': {'value_style': 'color: #ff0055;', 'text_style': 'color: #ff0055;font-size: 100%;', 'unit_style': 'color: #ff0055;font-size: 90%;'}, 'icons': [], 'static_icons': [], 'precision': 0, 'namespace': 'default'})
    
        widgets["default-temperature"] = new basedisplay("default-temperature", "", "zen", {'widget_type': 'basedisplay', 'entity': 'sensor.temperature', 'entity_to_sub_entity_attribute': '', 'sub_entity': '', 'sub_entity_to_entity_attribute': '', 'fields': {'title': 'Temperature', 'title2': '', 'value': '', 'unit': '', 'state_text': ''}, 'static_css': {'title_style': 'color: #000;font-weight: bold;', 'title2_style': 'color: #000;', 'state_text_style': 'color: #ff0055;font-size: 100%;', 'widget_style': 'background-image: url(css/zen/img/zen_bg2.jpg);', 'container_style': ''}, 'css': {'value_style': 'color: #ff0055;', 'text_style': 'color: #ff0055;font-size: 100%;', 'unit_style': 'color: #ff0055;font-size: 90%;'}, 'icons': [], 'static_icons': [], 'units': '&deg;C', 'precision': 1, 'namespace': 'default'})
    
        widgets["default-humidity"] = new basedisplay("default-humidity", "", "zen", {'widget_type': 'basedisplay', 'entity': 'sensor.humidity', 'entity_to_sub_entity_attribute': '', 'sub_entity': '', 'sub_entity_to_entity_attribute': '', 'fields': {'title': 'Humidity', 'title2': '', 'value': '', 'unit': '', 'state_text': ''}, 'static_css': {'title_style': 'color: #000;font-weight: bold;', 'title2_style': 'color: #000;', 'state_text_style': 'color: #ff0055;font-size: 100%;', 'widget_style': 'background-image: url(css/zen/img/zen_bg2.jpg);', 'container_style': ''}, 'css': {'value_style': 'color: #ff0055;', 'text_style': 'color: #ff0055;font-size: 100%;', 'unit_style': 'color: #ff0055;font-size: 90%;'}, 'icons': [], 'static_icons': [], 'units': '%', 'precision': 1, 'namespace': 'default'})
    
        widgets["default-btiphone"] = new basedisplay("default-btiphone", "", "zen", {'widget_type': 'basedisplay', 'entity': 'sensor.kyu_iphone', 'entity_to_sub_entity_attribute': '', 'sub_entity': '', 'sub_entity_to_entity_attribute': '', 'fields': {'title': 'Kyu iPhone Confidence', 'title2': '', 'value': '', 'unit': '', 'state_text': ''}, 'static_css': {'title_style': 'color: #000;font-weight: bold;', 'title2_style': 'color: #000;', 'state_text_style': 'color: #ff0055;font-size: 100%;', 'widget_style': 'background-image: url(css/zen/img/zen_bg2.jpg);', 'container_style': ''}, 'css': {'value_style': 'color: #ff0055;', 'text_style': 'color: #ff0055;font-size: 100%;', 'unit_style': 'color: #ff0055;font-size: 90%;'}, 'icons': [], 'static_icons': [], 'units': '%', 'precision': 0, 'namespace': 'default'})
    
        widgets["default-reload"] = new basejavascript("default-reload", "", "zen", {'widget_type': 'basejavascript', 'command': 'location.reload(true)', 'fields': {'title': '', 'title2': '', 'icon': '', 'icon_style': ''}, 'icons': {'icon_active': 'fas-spinner fa-spin', 'icon_inactive': 'fas-sync'}, 'static_css': {'title_style': 'color: white;', 'title2_style': 'color: #000;', 'widget_style': 'background-image: url(css/zen/img/zen_bg2.jpg);'}, 'css': {'icon_active_style': 'color: #ff0055;', 'icon_inactive_style': 'color: #ff0055;'}, 'static_icons': [], 'namespace': 'default'})
    

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

    window.dashstream = new DashStream("ws", location.protocol, document.domain, location.port, "Main", widgets);

});