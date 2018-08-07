//
// Created by xmh on 18-8-7.
//

#include "render.hpp"
#include "random"
int main()
{
    html_engine::json json;
    for(auto i = 0;i<3;i++)
    {
        html_engine::json item;
        std::random_device rd;
        item["post_title"] = std::to_string(rd());
        item["content_abstract"] = std::to_string(rd())+"content";
        item["post_modified"] =  std::to_string(rd())+"post_modified";
        item["post_author"] = std::to_string(rd())+"post_author";
        item["number"] = 1024;
        item["float"] = 32.0123;
        html_engine::json number;
        for(auto i = 0;i<3;i++){
            number.push_back(i);
        }
        item["number_list"] = number;
        json.push_back(item);
    }
    html_engine::json root;
    root["article_list"] = json;
    auto view = html_engine::render("./home.html",root);
    std::cout<<view<<std::endl;
    return 0;
}