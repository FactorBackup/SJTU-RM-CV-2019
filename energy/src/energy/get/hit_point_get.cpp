//
// Created by xixiliadorabarry on 1/24/19.
//

#include "energy/energy.h"
#include "energy/constant.h"

using namespace cv;
using std::cout;
using std::endl;
using std::vector;

void Energy::getHitPoint(){
    int hit_position = 1000;
    int limit_angle = 6;
    int angle_interval = 60;

    if(energy_part_rotation==1){    //顺时针
        if(target_armor>=15 && target_armor<=15+limit_angle){
            hit_point.x = cycle_center.x + static_cast<int>(radius / 2);
            hit_point.y = cycle_center.y + static_cast<int>(radius * sqrt(3) / 2);
            hit_position = -1*angle_interval;
        }
//        if(target_armor>=angle_interval && target_armor<angle_interval+limit_angle){
//            hit_point.x = cycle_center.x + static_cast<int>(radius);
//            hit_point.y = cycle_center.y;
//            hit_position = 0;
//        }
//        if(target_armor>=angle_interval*2 && target_armor<=angle_interval*2+limit_angle){
//            hit_point.x = cycle_center.x + static_cast<int>(radius / 2);
//            hit_point.y = cycle_center.y - static_cast<int>(radius * sqrt(3) / 2);
//            hit_position = angle_interval;
//        }
//        if(target_armor>=-180 && target_armor<-180+limit_angle){
//            hit_point.x = cycle_center.x - static_cast<int>(radius / 2);
//            hit_point.y = cycle_center.y - static_cast<int>(radius * sqrt(3) / 2);
//            hit_position = 2*angle_interval;
//        }
//        if(target_armor>=-2*angle_interval&&target_armor<-2*angle_interval+limit_angle){
//            hit_point.x = cycle_center.x - static_cast<int>(radius);
//            hit_point.y = cycle_center.y;
//            hit_position = 180;
//        }
//        if(target_armor>=-1*angle_interval&&target_armor<-1*angle_interval+limit_angle) {
//            hit_point.x = cycle_center.x - static_cast<int>(radius / 2);
//            hit_point.y = cycle_center.y + static_cast<int>(radius * sqrt(3) / 2);
//            hit_position = -2 * angle_interval;
//        }
        else{
            last_hit_position = 2000;
            return;
        }
    }

    if(energy_part_rotation==-1){    //逆时针
        if(target_armor>=0 && target_armor<=limit_angle){
            hit_point.x = cycle_center.x - static_cast<int>(radius / 2);
            hit_point.y = cycle_center.y - static_cast<int>(radius * sqrt(3) / 2);
            hit_position = 2*angle_interval;
        }
        if(target_armor>=angle_interval && target_armor<angle_interval+limit_angle){
            hit_point.x = cycle_center.x - static_cast<int>(radius);
            hit_point.y = cycle_center.y;
            hit_position = 180;
        }
        if(target_armor>=angle_interval*2 && target_armor<=angle_interval*2+limit_angle){
            hit_point.x = cycle_center.x - static_cast<int>(radius / 2);
            hit_point.y = cycle_center.y + static_cast<int>(radius * sqrt(3) / 2);
            hit_position = -2*angle_interval;
        }
        if(target_armor>=-180 && target_armor<-180+limit_angle){
            hit_point.x = cycle_center.x + static_cast<int>(radius / 2);
            hit_point.y = cycle_center.y + static_cast<int>(radius * sqrt(3) / 2);
            hit_position = -1*angle_interval;
        }
        if(target_armor>=-2*angle_interval&&target_armor<-2*angle_interval+limit_angle){
            hit_point.x = cycle_center.x + static_cast<int>(radius);
            hit_point.y = cycle_center.y;
            hit_position = 0;
        }
        if(target_armor>=-1*angle_interval&&target_armor<-1*angle_interval+limit_angle){
            hit_point.x = cycle_center.x + static_cast<int>(radius / 2);
            hit_point.y = cycle_center.y - static_cast<int>(radius * sqrt(3) / 2);
            hit_position = angle_interval;
        }
        else{
            last_hit_position = 2000;
            return;
        }
    }

    if(hit_position>360&&last_hit_position>360){
        isSendTarget = false;
        return;
    }

    if(fabs(hit_position - last_hit_position) < 30||fabs(hit_position - last_hit_position) > 330 && fabs(hit_position - last_hit_position) <= 360){
        last_hit_position = hit_position;
        isSendTarget = false;
        return;
    }
    else{
        last_hit_position = hit_position;
        isSendTarget = true;
        cout<<"hit position: "<<hit_position<<endl;
        return;
    }

//    double rad = static_cast<double>(energy_part_rotation * energy_part_param_.RPM
//                * energy_part_param_.HIT_TIME * 360 / 60);
//    rotate(rad, radius, cycle_center, target_center, hit_point);
}

bool Energy::changeTarget(){
    if(fabs(target_position - last_target_position) < 30||fabs(target_position - last_target_position) > 330){
        last_target_position = target_position;
        return false;
    }
    else{
        last_target_position = target_position;
        return true;
    }
}