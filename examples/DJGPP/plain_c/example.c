#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "cLDtk.h"


//------------------------------------------------
//          How to compile for DJGPP
//------------------------------------------------
//      $> gcc -c cLDtk.c parson.c -std=c99
//      $> ar rvs libcLDtk.a cLDtk.o parson.o
//      $> gcc example.c -o example.exe libcLDtk.a -std=c99
//
//

int main(void){

    
    // parameters: fileSchema, fileName
	// must chage JSON file to txt for MS-DOS 8(name).3(extension) file format
    loadJSONFile("{\"jsonVersion\":\"\"}","map.txt");
    
    importMapData();

    //Need to free pointer due to malloc in getEntity()
    struct entityInstances *mob;

    struct levels *level1;

    //Get level data
    level1 = getLevel("Level_1"); 
    //Get entity data
    mob = getEntity("Mob",level1->uid);

    
    //------------------------------------------------
    //              Display Entity Details
    //------------------------------------------------

    //Get entity count
    printf("Entity Instances Size: %d\n",mob->size);
    for(int f =0; f<mob->size;f++){
        //Display each entity identifier and coordinate position
        printf("----------------1---------------\n"); 
        printf("%d Identifier:%s\n",f+1,mob[f].identifier);
        printf("X:%d, Y:%d\n",mob[f].x,mob[f].y);
        
        printf("----------------2---------------\n"); 

        //Display each entity fieldInstance
        for(int i =0; i<mob[f].fieldInstanceCount;i++){
            printf("fieldInstance.identifier:%s\n",mob[f].fieldInstances_data_ptr[i].identifier);
            printf("fieldInstance.type:%s\n", mob[f].fieldInstances_data_ptr[i].type);
            printf("-------------------3-------------------\n"); 
            

            //Get array points from entity
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
            //Get arrays of: int and boolen from entity
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
            
            
            //Get color, filepath, enum, and string from entity
            //Must check substring with 9 chars, as there are multiple enum types
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
            //Get int, boolean from entity
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
            //Get float and float array from entity
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
            //Get arrays of: enums, filepath, color, string from entity
            //Must check substring with 15 chars, as there are multiple array enum types
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

    //------------------------------------------------
     


    


    //----------------------------------------------------------------
    //                  FREE UP MEMORY and Unload JSON file
    //----------------------------------------------------------------
    free(mob);
    

    freeMapData();

    json_value_free(schema);
    json_value_free(user_data);
    //----------------------------------------------------------------

    



    return 0;


}
