/* 
 * File:   robot_mover.h
 * Author: Parth
 *
 * Created on July 15, 2012, 2:07 PM
 */

#ifndef ROBOT_MOVER_H
#define	ROBOT_MOVER_H

// a data structure to hold the coordinates
struct coordinate
{
    float x, y, z;
    float angle, r;//in case polar coordinates
};
// a data structure to be used as interface for telling how much movement is needed
struct movement
{
    float angle, distance;
};

struct move_event
{
    struct coordinate move_to;
    struct move_event *next;
};

struct marker_cord
{
    coordinate location;
    int tag;
};


void robot_move_distance(double distance);
struct movement robot_cord_to_move(struct coordinate move_to_cord);
void next_move(struct coordinate next_move);
void get_curr_location(struct coordinate* location);
void get_stargazer_coord(const stargazer_cu::Pose2DTagged::ConstPtr& data);
void translate_stargz_real_cord(struct coordinate *translate_loc, int marker_id);
void *event_reader(void *arg);
void get_event(struct move_event *event);
void set_event(struct move_event event);
float add_angle(float ang1, float ang2);
void robot_init();
void marker_init();
#endif	/* ROBOT_MOVER_H */

