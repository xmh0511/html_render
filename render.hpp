//
// Created by xmh on 18-8-7.
//

#ifndef UNTITLED_RENDER_HPP
#define UNTITLED_RENDER_HPP
#include "nlohmann_json.hpp"
#include "ginger.h"
#include <sstream>
#include <fstream>
#include <map>
namespace html_engine{
    using json = nlohmann::json;
    template<typename Object>
    void json_to_ginner_data_(const nlohmann::json& json,Object&& ginner_obj,const std::string& key);
    template<typename Object>
    void json_to_ginner_data(const nlohmann::json& json,Object&& view_data);

    template<typename Object>
    inline void json_to_ginner_data_(const nlohmann::json& json,Object&& ginner_obj,const std::string& key)
    {
        if(json.is_object()){
            ginner_obj[key] = std::map<std::string,ginger::object>{};
            for(auto it = json.begin(); it != json.end(); ++it)
            {
                auto name = it.key();
                json_to_ginner_data_(it.value(),std::move(ginner_obj[key]),name);
            }
        }else if(json.is_array()){
            std::vector<ginger::object> list;
            for(auto it = json.begin(); it != json.end(); ++it)
            {
                if(!(*it).is_object()){
                 if((*it).is_string()){
                     list.push_back((*it).get<std::string>());
                 }else if((*it).is_number_float()){
                     list.push_back((*it).get<double>());
                 }else if((*it).is_number_integer()){
                     list.push_back((*it).get<int>());
                 }else if((*it).is_boolean()){
                     list.push_back((*it).get<bool>());
                 }else if((*it).is_null()){
                     list.push_back(nullptr);
                 }else if((*it).is_number_unsigned()){
                     list.push_back((*it).get<unsigned int>());
                 }
                }else{
                    std::map<std::string,ginger::object> object_tmp;
                    json_to_ginner_data(*it,object_tmp);
                    list.push_back(object_tmp);
                }
            }
            ginner_obj[key] = list;
        }else if(json.is_string()){
            ginner_obj[key] = json.get<std::string>();
        }else if(json.is_number_float()){
            ginner_obj[key] = json.get<double>();
        } else if(json.is_number_integer()){
            ginner_obj[key] = json.get<int>();
        }else if(json.is_boolean()){
            ginner_obj[key] = json.get<bool>();
        }else if(json.is_null()){
            ginner_obj[key] = nullptr;
        }else if(json.is_number_unsigned()){
            ginner_obj[key] = json.get<unsigned int>();
        }
    }
    template<typename Object>
    inline void json_to_ginner_data(const nlohmann::json& json,Object&& view_data)
    {
        for(auto iter = json.begin(); iter != json.end(); ++iter){
            json_to_ginner_data_(iter.value(),std::move(view_data),iter.key());
        }
    }

    inline std::string render(const std::string& tpl_filepath, const nlohmann::json& data)
    {
        std::stringstream buff;
        std::ifstream file(tpl_filepath);
        if(!file.is_open()){
            throw std::runtime_error("html template file is not open");
        }
        buff << file.rdbuf();
        std::stringstream result;
        std::map<std::string,ginger::object> view_data;
        json_to_ginner_data(data,std::move(view_data));
        ginger::parse(buff.str(),view_data,ginger::from_ios(result));
        return result.str();
    }
}
#endif //UNTITLED_RENDER_HPP
