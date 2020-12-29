
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <stdbool.h>

#include "cLDtk.h"
#include "parson.h"

int main(void){

    
    // parameters: fileSchema, fileName
    loadJSONFile("{\"jsonVersion\":\"\"}","test6.txt");
    
    importMapData();

        
    
 
    //Need to free pointer due to malloc in getEntity()
    //struct entityInstances *chest;
    struct entityInstances *mob;
    //struct entityInstances *player;

    //struct layerInstances *collisions;
    //struct layerInstances *bg_textures;

    struct levels *level1;


   /*
    collisions = getLayer("Collisions");
    printf("coordId:%d, v:%d\n",collisions->integerGrid_data_ptr[5].coordId,collisions->integerGrid_data_ptr[5].v);

    bg_textures = getLayer("Bg_textures");
    
    printf("bg_textures:%d\n",bg_textures->autoTiles_data_ptr[0].SRCx);
    */
    //chest = getEntity("Chest");
    
    level1 = getLevel("Adventure");
    
    
    mob = getEntity("Mob",level1->uid);



    /*
    player = getEntity("Player");
    
    printf("-----------------------------------------------------------\n"); 

    printf("Identifier:%s\n",player->identifier);
    printf("Player X:%d,Y:%d\n",player->x,player->y);

    player->x= 0; 
    player->y = 0;

    printf("Player X:%d,Y:%d\n",player->x,player->y);
    printf("Player Size:%d\n",player->size);
    
    printf("-----------------------------------------------------------\n"); 
    */

    //printf("Mob Size:%d\n",mob->size);
    

    printf("Entity Instances Size: %d\n",mob->size);
    for(int f =0; f<mob->size;f++){
        
        printf("----------------1---------------\n"); 
        printf("%d Identifier:%s\n",f+1,mob[f].identifier);
        printf("X:%d, Y:%d\n",mob[f].x,mob[f].y);
        
        printf("----------------2---------------\n"); 

        
        for(int i =0; i<mob[f].fieldInstanceCount;i++){
            printf("fieldInstance.identifier:%s\n",mob[f].fieldInstances_data_ptr[i].identifier);
            printf("fieldInstance.type:%s\n", mob[f].fieldInstances_data_ptr[i].type);
            printf("-------------------3-------------------\n"); 
            
 
            //Get array points from Entity
            
            if(strcmp(mob[f].fieldInstances_data_ptr[i].type,fieldInstance_array_point) == 0 || strcmp(mob[f].fieldInstances_data_ptr[i].type,fieldInstance_point) == 0){
                
                
                if(mob[f].fieldInstances_data_ptr[i].size > 0){
                    printf("Field Instance points Size: %d\n",mob[f].fieldInstances_data_ptr[i].fieldInstances_points_ptr->size);
                    for(int g=0;g<mob[f].fieldInstances_data_ptr[i].fieldInstances_points_ptr->size;g++){

                    //Cheat check to handle NULL values until I find a better way
                    if(mob[f].fieldInstances_data_ptr[i].fieldInstances_points_ptr[g].check != 1) break;
                    printf("Point X:%d,Y:%d\n",mob[f].fieldInstances_data_ptr[i].fieldInstances_points_ptr[g].cx,mob[f].fieldInstances_data_ptr[i].fieldInstances_points_ptr[g].cy);
                    
                    }
                }
               
                
                printf("-------------------4-------------------\n"); 
               
            }

            if(strcmp(mob[f].fieldInstances_data_ptr[i].type,fieldInstance_array_int) == 0 ||
               strcmp(mob[f].fieldInstances_data_ptr[i].type,fieldInstance_array_boolean) == 0 ){
                
                
                if(mob[f].fieldInstances_data_ptr[i].size > 0){
                    printf("Field Instance Ints Size: %d\n",mob[f].fieldInstances_data_ptr[i].fieldInstances_ints_ptr->size);
                    for(int g=0;g<mob[f].fieldInstances_data_ptr[i].fieldInstances_ints_ptr->size;g++){

                    //Cheat check to handle NULL values until I find a better way
                    if(mob[f].fieldInstances_data_ptr[i].fieldInstances_ints_ptr[g].check != 1) break;
                    printf("Int Value: %d\n",mob[f].fieldInstances_data_ptr[i].fieldInstances_ints_ptr[g].intValue);
                    
                    }
                }
               
                
                printf("-------------------4-------------------\n"); 
               
            }
            
            
                
            if(strcmp(mob[f].fieldInstances_data_ptr[i].type,fieldInstance_color) == 0 || 
            strcmp(mob[f].fieldInstances_data_ptr[i].type,fieldInstance_filePath) == 0 ||
            strncmp(mob[f].fieldInstances_data_ptr[i].type,fieldInstance_localEnum,9) == 0 ||
            strcmp(mob[f].fieldInstances_data_ptr[i].type,fieldInstance_string) == 0){

 
                if(mob[f].fieldInstances_data_ptr[i].size > 0){
                
                    for(int g=0;g<mob[f].fieldInstances_data_ptr[i].fieldInstances_strings_ptr->size;g++){
                        if(mob[f].fieldInstances_data_ptr[i].fieldInstances_strings_ptr[g].check != 1) break;
                        if(mob[f].fieldInstances_data_ptr[i].fieldInstances_strings_ptr[g].strValue != NULL){
                            printf("String: %s\n",mob[f].fieldInstances_data_ptr[i].fieldInstances_strings_ptr[g].strValue);
                        }    
                    }

                }
                
                printf("-------------------5-------------------\n"); 
                
            }
            
            if(strcmp(mob[f].fieldInstances_data_ptr[i].type,fieldInstance_integer) == 0 ||
               strcmp(mob[f].fieldInstances_data_ptr[i].type,fieldInstance_boolean) == 0){

 
                if(mob[f].fieldInstances_data_ptr[i].size > 0){
                
                    for(int g=0;g<mob[f].fieldInstances_data_ptr[i].fieldInstances_ints_ptr->size;g++){
                        if(mob[f].fieldInstances_data_ptr[i].fieldInstances_ints_ptr[g].check != 1) break;
                        
                        printf("Number: %d\n",mob[f].fieldInstances_data_ptr[i].fieldInstances_ints_ptr[g].intValue);
                    }

                }
                
                printf("-------------------5-------------------\n"); 
                
            }

            if(strcmp(mob[f].fieldInstances_data_ptr[i].type,fieldInstance_float) == 0 ||
               strcmp(mob[f].fieldInstances_data_ptr[i].type,fieldInstance_array_float) == 0){

 
                if(mob[f].fieldInstances_data_ptr[i].size > 0){
                
                    for(int g=0;g<mob[f].fieldInstances_data_ptr[i].fieldInstances_floats_ptr->size;g++){
                        if(mob[f].fieldInstances_data_ptr[i].fieldInstances_floats_ptr[g].check != 1) break;
                        
                        printf("Number: %g\n",mob[f].fieldInstances_data_ptr[i].fieldInstances_floats_ptr[g].floatValue);
                    }

                }
                
                printf("-------------------5-------------------\n"); 
                
            }

            if(strncmp(mob[f].fieldInstances_data_ptr[i].type,fieldInstance_array_localEnum,15) == 0 ||
            strcmp(mob[f].fieldInstances_data_ptr[i].type,fieldInstance_array_filePath) == 0 ||
            strcmp(mob[f].fieldInstances_data_ptr[i].type,fieldInstance_array_color) == 0 ||
            strcmp(mob[f].fieldInstances_data_ptr[i].type,fieldInstance_array_string) == 0 ){

 
                if(mob[f].fieldInstances_data_ptr[i].size > 0){
                
                    for(int g=0;g<mob[f].fieldInstances_data_ptr[i].fieldInstances_strings_ptr->size;g++){
                        if(mob[f].fieldInstances_data_ptr[i].fieldInstances_strings_ptr[g].check != 1) break;
                        
                        if(mob[f].fieldInstances_data_ptr[i].fieldInstances_strings_ptr[g].strValue != NULL){
                            printf("String: %s\n",mob[f].fieldInstances_data_ptr[i].fieldInstances_strings_ptr[g].strValue);
                        }
                    }

                }
                
                printf("-------------------5-------------------\n"); 
                
            }
			



            
            
        }
    }
    

    printf("-----------------------------------------------------------\n"); 

    

    
    //printf("Chest Size:%d\n",chest->size);
    /*
    for(int f =0; f<chest->size;f++){
        if(chest[f].identifier == NULL) break;
        printf("-------------------------------\n"); 
        printf("Identifier:%s\n",chest[f].identifier);
        printf("X:%d, Y:%d\n",chest[f].x,chest[f].y);
        printf("-------------------------------\n"); 
        for(int i =0; i<chest[f].fieldInstances_data_ptr->size;i++){
            
            printf("fieldInstance.identifier:%s\n",chest[f].fieldInstances_data_ptr[i].identifier);
            printf("--------------------------------------\n"); 

            
            for(int g=0;g<chest[f].fieldInstances_data_ptr[i].fieldInstances_points_ptr->size;g++){
                //if(chest[f].fieldInstances_data_ptr[i].fieldInstances_points_ptr[g].item == NULL) break;
                
                
                printf("fieldInstance_item.value:%s\n",chest[f].fieldInstances_data_ptr[i].fieldInstances_points_ptr[g].item);
            }
        }
    }
    */
   

    

    
    


    


    //----------------------------------------------------------------
    //                  FREE UP MEMORY and Unload JSON file
    //----------------------------------------------------------------
    //free(player);
    //free(chest);
    free(mob);
    

    freeTilesetData();
    freeEnumsData();
    freeLevelsData();

    json_value_free(schema);
    json_value_free(user_data);
    //----------------------------------------------------------------

    



    return 0;


}
