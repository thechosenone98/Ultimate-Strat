#include <xc.h>
#include "images.h"
#include "guitar_image.h"
#include "waveshare29epaper.h"

// <editor-fold defaultstate="collapsed" desc="PICKUP CONFIGURATION DEFINITION">
//Definition of all possible pickup configuration
#define X_IMG {.length = 0,.image_pointers = {},}
#define X_COIL 0x00
#define N_IMG {.length = 1,.image_pointers = {n_rot},}
#define N_COIL 0xA00
#define S_IMG {.length = 1,.image_pointers = {s_rot},}
#define S_COIL 0x500
#define N_PRIME_IMG {.length = 1,.image_pointers = {n_prime_rot},}
#define N_PRIME_COIL 0xC0
#define S_PRIME_IMG {.length = 1,.image_pointers = {s_prime_rot},}
#define S_PRIME_COIL 0x30
#define N_SERIE_S_IMG {.length = 3,.image_pointers = {n_rot, serie_rot, s_rot},}
#define N_SERIE_S_COIL 0x908
#define S_SERIE_N_IMG {.length = 3,.image_pointers = {s_rot, serie_rot, n_rot},}
#define S_SERIE_N_COIL 0x806
#define N_SERIE_S_PRIME_IMG {.length = 3,.image_pointers = {n_rot, serie_rot, s_prime_rot},}
#define N_SERIE_S_PRIME_COIL 0x824
#define S_PRIME_SERIE_N_IMG {.length = 3,.image_pointers = {s_prime_rot, serie_rot, n_rot},}
#define S_PRIME_SERIE_N_COIL 0x212
#define N_PRIME_SERIE_S_IMG {.length = 3,.image_pointers = {n_prime_rot, serie_rot, s_rot},}
#define N_PRIME_SERIE_S_COIL 0x142
#define S_SERIE_N_PRIME_IMG {.length = 3,.image_pointers = {s_rot, serie_rot, n_prime_rot},}
#define S_SERIE_N_PRIME_COIL 0x484
#define N_PRIME_SERIE_S_PRIME_IMG {.length = 3,.image_pointers = {n_prime_rot, serie_rot, s_prime_rot},}
#define N_PRIME_SERIE_S_PRIME_COIL 0x61
#define S_PRIME_SERIE_N_PRIME_IMG {.length = 3,.image_pointers = {s_prime_rot, serie_rot, n_prime_rot},}
#define S_PRIME_SERIE_N_PRIME_COIL 0x98
#define N_PARALLEL_S_IMG {.length = 3,.image_pointers = {n_rot, parallel_rot, s_rot},}
#define N_PARALLEL_S_COIL 0xF00
#define N_PRIME_PARALLEL_S_IMG {.length = 3,.image_pointers = {n_prime_rot, parallel_rot, s_rot},}
#define N_PRIME_PARALLEL_S_COIL 0x5C0
#define N_PARALLEL_S_PRIME_IMG {.length = 3,.image_pointers = {n_rot, parallel_rot, s_prime_rot},}
#define N_PARALLEL_S_PRIME_COIL 0xA30
#define N_PRIME_PARALLEL_S_PRIME_IMG {.length = 3,.image_pointers = {n_prime_rot, parallel_rot, s_prime_rot},}
#define N_PRIME_PARALLEL_S_PRIME_COIL 0xF0
// </editor-fold>
// <editor-fold defaultstate="collapsed" desc="GENERAL PICKUP CONFIGURATION DEFINITION">
//Only reason for the G is because the N configuration also exist for "North in the pickup configuration images
#define GN_IMG {.length = 1,.image_pointers = {n_rot},}
#define GN_COIL 0x900
#define M_IMG {.length = 1,.image_pointers = {m_rot},}
#define M_COIL 0x480
#define B_IMG {.length = 1,.image_pointers = {b_rot},}
#define B_COIL 0x240
#define N_SERIE_M_IMG {.length = 3,.image_pointers = {n_rot, serie_rot, m_rot},}
#define N_SERIE_M_COIL 0x8A0
#define M_SERIE_N_IMG {.length = 3,.image_pointers = {m_rot, serie_rot, n_rot},}
#define M_SERIE_N_COIL 0x504
#define N_SERIE_B_IMG {.length = 3,.image_pointers = {n_rot, serie_rot, b_rot},}
#define N_SERIE_B_COIL 0x850
#define B_SERIE_N_IMG {.length = 3,.image_pointers = {b_rot, serie_rot, n_rot},}
#define B_SERIE_N_COIL 0x302
#define M_SERIE_B_IMG {.length = 3,.image_pointers = {m_rot, serie_rot, b_rot},}
#define M_SERIE_B_COIL 0x448
#define B_SERIE_M_IMG {.length = 3,.image_pointers = {b_rot, serie_rot, m_rot},}
#define B_SERIE_M_COIL 0x281
#define N_SERIE_M_SERIE_B_IMG {.length = 5,.image_pointers = {n_rot, serie_rot, m_rot, serie_rot, b_rot},}
#define N_SERIE_M_SERIE_B_COIL 0x868
#define N_SERIE_B_SERIE_M_IMG {.length = 5,.image_pointers = {n_rot, serie_rot, b_rot, serie_rot, m_rot},}
#define N_SERIE_B_SERIE_M_COIL 0x891
#define B_SERIE_N_SERIE_M_IMG {.length = 5,.image_pointers = {b_rot, serie_rot, n_rot, serie_rot, m_rot},}
#define B_SERIE_N_SERIE_M_COIL 0x2A2
#define B_SERIE_M_SERIE_N_IMG {.length = 5,.image_pointers = {b_rot, serie_rot, m_rot, serie_rot, n_rot},}
#define B_SERIE_M_SERIE_N_COIL 0x305
#define N_PARALLEL_M_IMG {.length = 3,.image_pointers = {n_rot, parallel_rot, m_rot},}
#define N_PARALLEL_M_COIL 0xD80
#define N_PARALLEL_B_IMG {.length = 3,.image_pointers = {n_rot, parallel_rot, b_rot},}
#define N_PARALLEL_B_COIL 0xB40
#define M_PARALLEL_B_IMG {.length = 3,.image_pointers = {m_rot, parallel_rot, b_rot},}
#define M_PARALLEL_B_COIL 0x6C0
#define N_PARALLEL_M_PARALLEL_B_IMG {.length = 5,.image_pointers = {n_rot, parallel_rot, m_rot, parallel_rot, b_rot},}
#define N_PARALLEL_M_PARALLEL_B_COIL 0xFC0
#define N_PARALLEL_M_SERIE_B_IMG {.length = 5,.image_pointers = {n_rot, parallel_rot, m_rot, serie_rot, b_rot},}
#define N_PARALLEL_M_SERIE_B_COIL 0xC58
#define B_SERIE_N_PARALLEL_M_IMG {.length = 5,.image_pointers = {b_rot, serie_rot, n_rot, parallel_rot, m_rot},}
#define B_SERIE_N_PARALLEL_M_COIL 0x383
#define N_SERIE_M_PARALLEL_B_IMG {.length = 5,.image_pointers = {n_rot, serie_rot, m_rot, parallel_rot, b_rot},}
#define N_SERIE_M_PARALLEL_B_COIL 0x8F0
#define M_PARALLEL_B_SERIE_N_IMG {.length = 5,.image_pointers = {m_rot, parallel_rot, b_rot, serie_rot, n_rot},}
#define M_PARALLEL_B_SERIE_N_COIL 0x706
#define N_PARALLEL_B_SERIE_M_IMG {.length = 5,.image_pointers = {n_rot, parallel_rot, b_rot, serie_rot, m_rot},}
#define N_PARALLEL_B_SERIE_M_COIL 0xAA1
#define M_SERIE_N_PARALLEL_B_IMG {.length = 5,.image_pointers = {m_rot, serie_rot, n_rot, parallel_rot, b_rot},}
#define M_SERIE_N_PARALLEL_B_COIL 0x54C
// </editor-fold>


PickupConfigurationImage pci[17] = {
    X_IMG, N_IMG, S_IMG, N_PRIME_IMG, S_PRIME_IMG, N_SERIE_S_IMG, S_SERIE_N_IMG, N_SERIE_S_PRIME_IMG, 
    S_PRIME_SERIE_N_IMG, N_PRIME_SERIE_S_IMG, S_SERIE_N_PRIME_IMG, N_PRIME_SERIE_S_PRIME_IMG, 
    S_PRIME_SERIE_N_PRIME_IMG, N_PARALLEL_S_IMG, N_PRIME_PARALLEL_S_IMG, N_PARALLEL_S_PRIME_IMG, 
    N_PRIME_PARALLEL_S_PRIME_IMG
};

GeneralPickupConfigurationImage gpci[23] = {
    GN_IMG, M_IMG, B_IMG, N_SERIE_M_IMG, M_SERIE_N_IMG, N_SERIE_B_IMG, B_SERIE_N_IMG, M_SERIE_B_IMG, 
    B_SERIE_M_IMG, N_SERIE_M_SERIE_B_IMG, N_SERIE_B_SERIE_M_IMG, B_SERIE_N_SERIE_M_IMG, B_SERIE_M_SERIE_N_IMG,
    N_PARALLEL_M_IMG, N_PARALLEL_B_IMG, M_PARALLEL_B_IMG, N_PARALLEL_M_PARALLEL_B_IMG, N_PARALLEL_M_SERIE_B_IMG,
    B_SERIE_N_PARALLEL_M_IMG, N_SERIE_M_PARALLEL_B_IMG, M_PARALLEL_B_SERIE_N_IMG, N_PARALLEL_B_SERIE_M_IMG,
    M_SERIE_N_PARALLEL_B_IMG
};

const uint16_t pickup_configuration_selectors[17] = {
    X_COIL, N_COIL, S_COIL, N_PRIME_COIL, S_PRIME_COIL, N_SERIE_S_COIL, S_SERIE_N_COIL, N_SERIE_S_PRIME_COIL,
    S_PRIME_SERIE_N_COIL, N_PRIME_SERIE_S_COIL, S_SERIE_N_PRIME_COIL, N_PRIME_SERIE_S_PRIME_COIL,
    S_PRIME_SERIE_N_PRIME_COIL, N_PARALLEL_S_COIL, N_PRIME_PARALLEL_S_COIL, N_PARALLEL_S_PRIME_COIL,
    N_PRIME_PARALLEL_S_PRIME_COIL
};

const uint16_t general_pickup_configuration_selectors[23] = {
    GN_COIL, M_COIL, B_COIL, N_SERIE_M_COIL, M_SERIE_N_COIL, N_SERIE_B_COIL, B_SERIE_N_COIL, M_SERIE_B_COIL, 
    B_SERIE_M_COIL, N_SERIE_M_SERIE_B_COIL, N_SERIE_B_SERIE_M_COIL, B_SERIE_N_SERIE_M_COIL, B_SERIE_M_SERIE_N_COIL,
    N_PARALLEL_M_COIL, N_PARALLEL_B_COIL, M_PARALLEL_B_COIL, N_PARALLEL_M_PARALLEL_B_COIL, N_PARALLEL_M_SERIE_B_COIL,
    B_SERIE_N_PARALLEL_M_COIL, N_SERIE_M_PARALLEL_B_COIL, M_PARALLEL_B_SERIE_N_COIL, N_PARALLEL_B_SERIE_M_COIL,
    M_SERIE_N_PARALLEL_B_COIL
};


void ClearLine(uint16_t start_x, uint8_t max_character){
    //Clear this line on the screen (double buffer mean when we refresh we are on the new buffer which contains old data)
    uint16_t start_y = (EPD_HEIGHT >> 1) + ((max_character * character_height_rot + arrow_image_height_rot) >> 1);
    ClearFrameMemoryPartial(start_x, start_y - (max_character * character_height_rot + arrow_image_height_rot), start_x + character_width_rot - 5, start_y, 0xFF); //Check that -5 later because I don't understand exactly why it is necessary (erases part of the next line otherwise)
}

void ImageFromPickupConf(PickupConfiguration* pc, int8_t selection_index, bool bracket, bool draw_empty){
    //Create Neck Pickup Image
    uint8_t max_index = 0;
    int8_t index = 0;
    uint16_t start_x = 0;
    uint16_t start_y = 0;
    
    int8_t pickup_indexes[4];
    pickup_indexes[0] = pc->neck;
    pickup_indexes[1] = pc->middle;
    pickup_indexes[2] = pc->bridge;
    pickup_indexes[3] = pc->general;
    unsigned char *arrow_type[4];
    arrow_type[0] = n_arrow_rot;
    arrow_type[1] = m_arrow_rot;
    arrow_type[2] = b_arrow_rot;
    arrow_type[3] = g_arrow_rot;
    
    if(selection_index >= 0){ //Select mode
        //Refresh only the part being updated
        start_x = (EPD_WIDTH >> 1) - ((4 * character_width_rot) >> 1); //Always 4 line high while making the selection
        start_x += character_width_rot * (uint8_t)selection_index;
        
        if(selection_index < 3){
            ClearLine(start_x, 5);
            max_index = pci[pickup_indexes[selection_index]].length;
        }
        else{
            ClearLine(start_x, 7);
            max_index = gpci[pickup_indexes[selection_index]].length;
        }
        
        start_y = (EPD_HEIGHT >> 1) + (((max_index + 2) * character_height_rot + arrow_image_height_rot) >> 1);
        start_y -= character_height_rot;
        if(bracket)
            SetFrameMemoryPartial(bracket_left_rot, start_x, start_y, character_width_rot, character_height_rot, true);
        //Draw the N with an arrow
        start_y -= arrow_image_height_rot;
        SetFrameMemoryPartial(arrow_type[selection_index], start_x, start_y, arrow_image_width_rot, arrow_image_height_rot, true);
        //Draw the pickup configuration image
        while(index < max_index){
            start_y -= character_height_rot;
            if(selection_index < 3)
                SetFrameMemoryPartial(pci[pickup_indexes[selection_index]].image_pointers[index], start_x, start_y, character_width_rot, character_height_rot, true);
            else
                SetFrameMemoryPartial(gpci[pickup_indexes[selection_index]].image_pointers[index], start_x, start_y, character_width_rot, character_height_rot, true);
            index++;
        }
        //Draw the right bracket
        start_y -= character_height_rot;
        if(bracket)
            SetFrameMemoryPartial(bracket_right_rot, start_x, start_y, character_width_rot, character_height_rot, true);
    } else { //Display and sleep
        //Clear Entire Display Buffer
        ClearFrameMemory(0xFF);
        //Add Neck indicator image to the buffer
        //Since we know to total width of the image to display (because we know all character width and the pickup configuration)
        //We can center the image right as we put it in, no need to fill another buffer and copy it centered after the fact.
        start_x = (EPD_WIDTH >> 1) - (((((pc->neck == 0) && !draw_empty ? 0 : 1) + ((pc->middle == 0) && !draw_empty ? 0 : 1) + ((pc->bridge == 0) && !draw_empty ? 0 : 1) + 1) * character_width_rot) >> 1);
        
        bool need_to_draw_row[4];
        need_to_draw_row[0] = pc->neck != 0 || draw_empty;
        need_to_draw_row[1] = pc->middle != 0 || draw_empty;
        need_to_draw_row[2] = pc->bridge != 0 || draw_empty;
        need_to_draw_row[3] = true; // This row is always drawn (no empty option))
        bool need_to_skip_row[4];
        need_to_skip_row[0] = false;
        need_to_skip_row[1] = pc->neck != 0 || draw_empty;
        need_to_skip_row[2] = need_to_skip_row[1] || pc->middle != 0;
        need_to_skip_row[3] = need_to_skip_row[2] || pc->bridge != 0;
        int i;
        for(i = 0; i < 4; ++i)
        {
            if(need_to_draw_row[i])
            {
                if(i < 3)
                    max_index = pci[pickup_indexes[i]].length;
                else
                    max_index = gpci[pickup_indexes[i]].length;
                if(need_to_skip_row[i])
                    start_x += character_width_rot;
                start_y = (EPD_HEIGHT >> 1) + ((max_index * character_height_rot + arrow_image_height_rot) >> 1);
                start_y -= arrow_image_height_rot;
                SetFrameMemoryPartial(arrow_type[i], start_x, start_y, arrow_image_width_rot, arrow_image_height_rot, true);
                index = 0;
                while(index < max_index)
                {
                    start_y -= character_height_rot;
                    if(i < 3)
                        SetFrameMemoryPartial(pci[pickup_indexes[i]].image_pointers[index], start_x, start_y, character_width_rot, character_height_rot, true);
                    else
                        SetFrameMemoryPartial(gpci[pickup_indexes[i]].image_pointers[index], start_x, start_y, character_width_rot, character_height_rot, true);
                    index++;
                }
            }
        }
    }
}
