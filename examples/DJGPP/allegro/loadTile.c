#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <stdbool.h>

#include "cLDtk.h"
#include <allegro.h>

//------------------------------------------------
//          How to compile for DJGPP\ALLEGRO
//------------------------------------------------
//      $> gcc -c cLDtk.c parson.c -std=c99
//      $> ar rvs libcLDtk.a cLDtk.o parson.o
//      $> gcc example.c -o example.exe libcLDtk.a -std=c99 -lalleg
//
//


 

void DrawTiles(struct layerInstances *layer,BITMAP *texture,BITMAP *buffer,int offset){

    BITMAP *bmp = NULL; //tmp used to hold flipped tiles
    bmp = create_bitmap(offset,offset);
    clear_bitmap(bmp);

	for(int y=layer->autoTiles_data_ptr->count ;y-- > 0;){ 
        
        masked_blit(texture, bmp, layer->autoTiles_data_ptr[y].SRCx, layer->autoTiles_data_ptr[y].SRCy, 0,
		     0, offset, offset);
        
        switch(layer->autoTiles_data_ptr[y].f){
            case 0 :
                draw_sprite(buffer,bmp,layer->autoTiles_data_ptr[y].x,layer->autoTiles_data_ptr[y].y);
                clear_bitmap(bmp);
            //flip horizontal
            case 1 :
                draw_sprite_h_flip(buffer,bmp,layer->autoTiles_data_ptr[y].x,layer->autoTiles_data_ptr[y].y);
                clear_bitmap(bmp);
            //flip vertical
            case 2 :
                draw_sprite_v_flip(buffer,bmp,layer->autoTiles_data_ptr[y].x,layer->autoTiles_data_ptr[y].y);
                clear_bitmap(bmp);
            //flip both
            case 3 :
               draw_sprite_vh_flip(buffer,bmp,layer->autoTiles_data_ptr[y].x,layer->autoTiles_data_ptr[y].y);
               clear_bitmap(bmp); 
        }  	
    }
    destroy_bitmap(bmp);
}
END_OF_FUNCTION(DrawTiles);

int main(int argc, char *argv[])
{
    allegro_init();
    install_keyboard();

    set_color_depth(8);

    set_gfx_mode(GFX_AUTODETECT, 320, 240, 0, 0);

    BITMAP *my_pic = NULL;
    PALETTE the_palette;
    my_pic = load_bitmap("sl.bmp",the_palette);
    
	
	BITMAP *buffer = NULL;
    buffer = create_bitmap(320,240);
	
	clear_keybuf();

    clear_bitmap(screen);
	clear_bitmap(buffer);

    // must chage JSON file to txt for MS-DOS 8(name).3(extension) file format
    loadJSONFile("{\"jsonVersion\":\"\"}","map.txt");
	
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
	
    set_palette(the_palette);
	//load background tiles
	DrawTiles(lvl_one_background,my_pic,buffer,16);
	//load foreground tiles
	DrawTiles(lvl_one_collisions,my_pic,buffer,16);
	
	//load from buffer to screen
    masked_blit(buffer, screen,0,0,0,0,320,240);
        
    readkey();

    destroy_bitmap(my_pic);
	destroy_bitmap(buffer);
	
	freeMapData();                // Unload map data
    
    json_value_free(schema);      // Unload JSON schema
    json_value_free(user_data);   // Unload JSON data
	
    return 0;   
}
END_OF_MAIN()
