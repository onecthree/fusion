#pragma once

#include <phpcpp.h>

#include <fusion/http/request/request.hpp>
#include <fusion/views/constra/constra.hpp>

#include <iostream>

class DefaultContainer {
    public: Php::Object object_class(std::string method_name) {
        std::map <std::string, Php::Object> dependencies_list;

        dependencies_list["Fusion\\Http\\Request"] = def_request();
        dependencies_list["Fusion\\Views\\Constra"] = def_constra();
    
        return dependencies_list[method_name];
    }

    /**
     * @note List all of default dependencies for DI Fusion.
     * 
     */

    public: Php::Object def_request() {
        Request *request = new Request;
        return Php::Object("Fusion\\Http\\Request", request);
    }
    
    public: Php::Object def_constra() {
        Constra *constra = new Constra;
        return Php::Object("Fusion\\Views\\Constra", constra);
    }

};