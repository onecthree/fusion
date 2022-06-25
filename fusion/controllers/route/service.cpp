#pragma once

#include <phpcpp.h>

#include <fusion/database/core.cpp>
#include <fusion/error/message.cpp>
#include <fusion/http/request/request.cpp>

#include <iostream>

namespace RouteService {
    class web : public Php::Base {
        public: void static patch(std::string uri_route) {
            Database::set::push_array_string({"FUSION_STORE", "FS_ROUTE", "FS_Web_Route_List"}, uri_route);
        }

        public: Php::Value static assign(std::string uri_route, Php::Value handler_opt) {
            std::string request_uri = Database::get::string({"FUSION_STORE", "FS_ROUTE", "FS_REQUEST_URI"});

            if(uri_route != request_uri)
                return 0;

            if(Php::is_array(handler_opt).boolValue()) {
                if(Php::count(handler_opt) < 2)
                    Error::message::handler_opt_empty_args();

                if(Php::count(handler_opt) > 2)
                    Error::message::handler_opt_many_args();

                std::string user_controller_name = handler_opt[0];
                const char* user_method_name     = handler_opt[1];

                Php::Object user_controller(user_controller_name);
                user_controller.call(user_method_name);

                return 0;
            }               

            if(Php::call("is_callable", handler_opt).boolValue()) {
                Request *request = new Request;

                handler_opt(Php::Object("Fusion\\Http\\Request", request));
                
                return 0;
            }

            return 0;
        }
    };
}