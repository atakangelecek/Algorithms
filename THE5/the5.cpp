#include "the5.h"

/* 
    in the5.h "struct Room" is defined as below:
    
    struct Room {
        int id;
        char content;
        vector<Room*> neighbors;
    };

*/

vector<int> maze_trace_helper(vector<Room*> maze, vector<int> path, bool* is_visited, stack<Room*> node_to_visit, stack<int> trace) {
    node_to_visit.push(maze[0]);

    while (!node_to_visit.empty()) {

        // Pop the top element from the stack
        Room* room = node_to_visit.top();
        node_to_visit.pop();
        if(is_visited[room->id] == false){
            // make visited true 
            is_visited[room->id] = true;
    
            if(room->content == '-'){
                bool unvisited_left = false;
                path.push_back(room->id);
    
                for (int i = room->neighbors.size() - 1; i >= 0; i--) {
                    
                    // eğer o room isvisited ise stacke pushlanmayacak
                    if(is_visited[(room->neighbors[i])->id] == false){
                        unvisited_left = true;
                        node_to_visit.push(room->neighbors[i]);
                    }
                }
                if(unvisited_left == true){
                    trace.push(room->id);
                }
    
                else if(unvisited_left == false){
                    while(!trace.empty()){
                        int room_id = trace.top();
                        path.push_back(room_id);
                        bool is_found = false;
                        
                        Room* found_room = NULL;
                        for(int i=0; i<maze.size(); i++){
                            if(maze[i]->id == room_id){
                                found_room = maze[i];
                                break;
                            }
                        }

                        for(int i=(found_room->neighbors.size() - 1); i >= 0; i--){
                            if(is_visited[(found_room->neighbors[i])->id] == false){
                                is_found = true;
                            }
                        }
    
                        // pop from trace and continue
                        if(is_found == false){
                            trace.pop();
                        } 
    
                        //break
                        else if(is_found == true){
                            break;
                        }   
                    }
                }
            }
    
            else if(room->content == '*'){
                path.push_back(room->id);
                while(!trace.empty()){
                    int roomId = trace.top();
                    trace.pop();
                    path.push_back(roomId);
                }
                break;    
            }
        }
    }
    return path;

}




vector<int> maze_trace(vector<Room*> maze) { 

    vector<int> path;
    stack<Room*> node_to_visit;
    stack<int> trace;
    bool is_visited[10000];
    for (int i = 0; i < 10000; i++){
        is_visited[i] = false;
    }
    
    return maze_trace_helper(maze, path, is_visited, node_to_visit, trace);
    // this is a dummy return value. YOU SHOULD CHANGE THIS!
}


