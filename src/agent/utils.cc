// Copyright (c) 2015, Galaxy Authors. All Rights Reserved
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.
//
// Author: yuanyi03@baidu.com

#include "agent/utils.h"

#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>
#include <fcntl.h>
#include <errno.h>
#include <string.h>
#include <time.h>

#include <boost/algorithm/string/predicate.hpp>
#include <boost/lexical_cast.hpp>

#include "common/logging.h"

namespace galaxy {

bool GetDirFilesByPrefix(const std::string& dir, const std::string& prefix, std::vector<std::string>* files) {
    DIR* dir_desc = opendir(dir.c_str());    
    if (dir_desc == NULL) {
        LOG(WARNING, "open dir failed err[%d: %s]",
                errno,
                strerror(errno)); 
        return false;
    }

    struct dirent* dir_entity;
    while ((dir_entity = readdir(dir_desc)) != NULL) {
        std::string log_file_name(dir_entity->d_name);
        if (!prefix.empty() 
                && !boost::starts_with(log_file_name,
                    prefix)) {
            continue; 
        }
        files->push_back(log_file_name);
    }
    return true;
}

void GetStrFTime(std::string* time_str) {
    const int TIME_BUFFER_LEN = 100;        
    char time_buffer[TIME_BUFFER_LEN];
    time_t seconds = time(NULL);
    struct tm t;
    localtime_r(&seconds, &t);
    size_t len = strftime(time_buffer,
            TIME_BUFFER_LEN - 1,
            "%Y%m%d%H%M%S",
            &t);
    time_buffer[len] = '\0';
    time_str->clear();
    time_str->append(time_buffer, len);
    return ;
}

}   // ending namespace galaxy

/* vim: set ts=4 sw=4 sts=4 tw=100 */
