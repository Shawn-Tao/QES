/*****************************************************************************
*  Copyright (c) 2021 BJTU, Inc.
*  Licensed under the Apache License, Version 2.0 (the "License");
*  you may not use this file except in compliance with the License.
*  You may obtain a copy of the License at
*      http://www.apache.org/licenses/LICENSE-2.0
*  Unless required by applicable law or agreed to in writing, software
*  distributed under the License is distributed outlookon an "AS IS" BASIS,
*  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
*  See the License for the specific language governing permissions and
*  limitations under the License.
*  Authors: Shawntao (shawntao-cn@outlook.com)
*  Date: 2021-12-04
*******************************************************************************/


#include "detect_task.h"

Detect_Message::Detect_Message(QObject *parent){

}

bool Detect_Message::send_file(){
    return false;
}

bool Detect_Message::send_str(){
    return false;
}

Detect_Task::Detect_Task(QObject *parent)
{

}

bool Detect_Task::start_detect()
{
    return false;
}

bool Detect_Task::stop_detect()
{
    return false;
}





