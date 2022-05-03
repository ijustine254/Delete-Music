//
// Created by Administrator on 5/3/2022.
//

#include "webserver.h"
#include "Socket.h"

void clear();
void Request_Handler(webserver::http_request* r) {
    Socket s = *(r->s_);

    std::string title;
    std::string body;
    std::string bgcolor="#ffffff";

    if(r->path_ == "/") {
        title = "Web Server";
        body  = "<h1>Welcome to Mimnet Script Engine</h1>";
    }
    else if (r->path_ == "/form") {
        title   = "Fill a form";

        body    = "<h1>Fill a form</h1>";
        body   += "<form action='/form'>"
                  "<table>"
                  "<tr><td>Field 1</td><td><input name=field_1></td></tr>"
                  "<tr><td>Field 2</td><td><input name=field_2></td></tr>"
                  "<tr><td>Field 3</td><td><input name=field_3></td></tr>"
                  "</table>"
                  "<input type=submit></form>";


        for (std::map<std::string, std::string>::const_iterator i = r->params_.begin();
             i != r->params_.end();
             i++) {

            body += "<br>" + i->first + " = " + i->second;
        }


        body += "<hr>" + links;

    }
    else if (r->path_ == "/auth") {
        if (r->authentication_given_) {
            if (r->username_ == "rene" && r->password_ == "secretGarden") {
                body = "<h1>Successfully authenticated</h1>" + links;
            }
            else {
                body = "<h1>Wrong username or password</h1>" + links;
                r->auth_realm_ = "Private Stuff";
            }
        }
        else {
            r->auth_realm_ = "Private Stuff";
        }
    }
    else if (r->path_ == "/clear") {
        //Clear Music from pc
        clear();
    }
    else {
        r->status_ = "404 Not Found";
        title      = "Wrong URL";
        body       = "<h1>Wrong URL</h1>";
        body      += "Path is : &gt;" + r->path_ + "&lt;";
    }

    r->answer_  = "<html><head><title>";
    r->answer_ += title;
    r->answer_ += "</title></head><body>";
    r->answer_ += body;
    r->answer_ += "</body></html>";
}

