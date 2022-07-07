#pragma once

#include <phpcpp.h>

class RoutePost : public Php::Base {

    // constructor
    public: RoutePost(Php::Parameters &param) {
        if(Php::count(param) < 2) 
            Error::message::empty_route_get_param();

        if(Php::count(param) > 2)
            Error::message::many_route_get_param();

        if(Php::eval("return $_SERVER['REQUEST_METHOD'];").stringValue() == "POST") {
            std::string uri_route   = param[0];
            std::string escape_uri_route = Regex::uri::escape_request_uri(uri_route + "/");
            Php::Value handler_opt  = param[1];

            RouteService::web::push(escape_uri_route);
            SmartRouter::catch_uri_parse(escape_uri_route);

            if(!Database::get::boolean({"FUSION_STORE", "FS_ROUTE", "FS_Route_V_Double"})) {
                std::string request_uri = Database::get::string({"FUSION_STORE", "FS_ROUTE", "FS_REQUEST_URI"});

                if(SmartRouter::handle_input_uri_guard(escape_uri_route) || uri_route == request_uri) {
                    RouteService::web::assign(escape_uri_route, handler_opt);
                }
            }
        }
    }
};