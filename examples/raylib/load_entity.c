#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "cLDtk.h"
#include "raylib.h"

//--------------------------------------------------------------------------------------
//                              Raylib specific functions
//--------------------------------------------------------------------------------------
void DrawSprite(Texture2D texture, Rectangle sourceRec, Vector2 position,int flip, Color tint);
void DrawTiles(struct layerInstances *layer,Texture2D texture,int offset,Color tint);
void DrawEntityRect(struct entityInstances *entity,int offset,int width,int height,Color tint);
//--------------------------------------------------------------------------------------

int main(void)
{
    // Initialization
    //--------------------------------------------------------------------------------------
    const int screenWidth = 816;
    const int screenHeight = 336;
    InitWindow(screenWidth, screenHeight, "raylib LDtk loader - Load Entity");

    // NOTE: Textures MUST be loaded after Window initialization (OpenGL context is required)
    Texture2D texture = LoadTexture("resources/SunnyLand_by_Ansimuz.png");        // Texture loading

    //Sprite size offset
    int offset = 16;
 

    SetTargetFPS(60);               // Set our game to run at 60 frames-per-second
    //--------------------------------------------------------------------------------------
    
    //Load the JSON file 
    loadJSONFile("{\"jsonVersion\":\"\"}","resources/map.json");

    //Import the map data from the JSON file into memory
    importMapData();

    //Get level data from memory   
    struct levels *lvl_one;
    lvl_one = getLevel("Level_1");
    
    //Get foreground layer data from memory
    struct layerInstances *lvl_one_collisions;
    lvl_one_collisions = getLayer("Collisions",lvl_one->uid);
    
    //Get background layer data from memory
    struct layerInstances *lvl_one_background;
    lvl_one_background = getLayer("Bg_textures",lvl_one->uid);
    
    //Get entity data from memory
    struct entityInstances *mob;
    mob = getEntity("Mob",lvl_one->uid);
    
    
        
    

    // Main game loop
    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        // Update
        //----------------------------------------------------------------------------------
        
        
        //----------------------------------------------------------------------------------

        // Draw
        //----------------------------------------------------------------------------------
        BeginDrawing();
        
        ClearBackground(BLACK);
            
            //Draw background
            DrawTiles(lvl_one_background,texture,offset,WHITE);
                
            //Draw foreground
            DrawTiles(lvl_one_collisions,texture,offset,WHITE);
            
            //Draw entity primative
            DrawEntityRect(mob,offset,16,16,RED);
            

        EndDrawing();
        //----------------------------------------------------------------------------------
    }

    // De-Initialization
    //--------------------------------------------------------------------------------------
    UnloadTexture(texture);       // Texture unloading
    
    free(mob);                    // Unload entity data
    
    freeMapData();                // Unload map data
    
    json_value_free(schema);      // Unload JSON schema
    json_value_free(user_data);   // Unload JSON data
    
    

    CloseWindow();                // Close window and OpenGL context
    //--------------------------------------------------------------------------------------

    return 0;
}

//--------------------------------------------------------------------------------------
//                              Raylib specific functions
//--------------------------------------------------------------------------------------



void DrawSprite(Texture2D texture, Rectangle sourceRec, Vector2 position,int flip, Color tint) 
{
    Rectangle destRec = { position.x, position.y, fabsf(sourceRec.width), fabsf(sourceRec.height) };
    Vector2 origin = { 0.0f, 0.0f };
    
    //flip=0;
    
    switch(flip){
        case 0 :
            //flipx =false; 
            //flipy = false;
            break;
        case 1 :
            //flipx = true; 
            //flipy = false;
            sourceRec.width *= -1;
            break;
        
        case 2 :
            //flipx = false; 
            //flipy = true;
            sourceRec.height *= -1;
            break;
        case 3 :
            //flipx = true; 
            //flipy = true;
            sourceRec.width *= -1;
            sourceRec.height *= -1;
            
            break;
            
    }
    
    

    DrawTexturePro(texture, sourceRec, destRec, origin, 0.0f, tint);
  
}

void DrawTiles(struct layerInstances *layer,Texture2D texture,int offset,Color tint)
{
    
    for(int y=layer->autoTiles_data_ptr->count ;y-- > 0;){ 
            
        DrawSprite(
            texture,
            (Rectangle){(float)layer->autoTiles_data_ptr[y].SRCx,(float)layer->autoTiles_data_ptr[y].SRCy,offset,offset},
            (Vector2){(float)layer->autoTiles_data_ptr[y].x,(float)layer->autoTiles_data_ptr[y].y},
            layer->autoTiles_data_ptr[y].f,
            tint);
    }

}

void DrawEntityRect(struct entityInstances *entity,int offset,int width,int height,Color tint)
{
    
    for(int f =0; f<entity->size;f++){
        
        //Need to adjust X and Y positions as they as based on the pivot point in LDtk
        DrawRectangle(entity[f].x-offset/2, entity[f].y-offset, width, height, tint);
                
    }

}   
//--------------------------------------------------------------------------------------
