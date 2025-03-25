// pcNY C: code pio-ESP32 millinewton.cpp

#include "Arduino.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define QUIET 1

void setup() {
  pinMode(LED_BUILTIN, OUTPUT);   // initialize LED digital pin as an output.
  Serial.begin(9600); // initialize serial communication at 9600 bits per second:
}

void loop() { // main code here, will run repeatedly
    int start = millis();

    int width  = 800; // smaller values
    int height = 600;   
    int iterations = 20;
    int y, x, i;   
    int r, root;

    /* Complex variables */
    double roots[3][2];         /* Solutions                */
    double z_re, z_im;          /* Complex iterator         */ 
    double num_re, num_im;      /* Numerator for update     */
    double den_re, den_im;      /* Denominator for update   */
    double tmp_re, tmp_im;      /* Update value             */
    double diff_re, diff_im;    /* Distance from solution   */

    // FILE *out = stdout; 

    // fprintf ( out, "P3 %d %d 255\n", width, height );
    #ifndef QUIET
        Serial.println("P3 800 600 255");  // TODO fix hardcoded values
    #else
        ;
    #endif
    roots[0][0] =  1.0, roots[0][1] =  0.0;
    roots[1][0] = -0.5, roots[1][1] =  sqrt(3.0)/2.0;
    roots[2][0] = -0.5, roots[2][1] = -sqrt(3.0)/2.0; 

    for ( y=0; y<height; y++ )
    {
        // Serial.print(" y:"); Serial.print(y); // DEBUG show progress
        for ( x=0; x<width; x++ )
        {  
              z_re = ( ( 2.0 * y - height ) / height );
              z_im = ( ( 2.0 * x - width ) / width ); 

            for ( i=0; i<iterations; i++ )
            {
                /* Formula for f(z) = z^3 - 1:
                 * z = z - (z*z*z - 1.0) / (3.0*z*z);
                 */

                /* Denominator = z*z */
                den_re = z_re*z_re - z_im*z_im; 
                den_im = 2.0 * z_re*z_im;  
  
                /* Numerator = z*z*z */  
                num_re = den_re*z_re - den_im*z_im;  
                num_im = den_re*z_im + den_im*z_re; 

                /* Denominator = 3 * z * z */        
                den_re = 3 * den_re;   
                den_im = 3 * den_im;    
 
                /* Numerator = z*z*z-1 */ 
                num_re = num_re - 1.0; 
  
                /* Update = Numerator / Denominator */
                tmp_re = ( num_re*den_re + num_im*den_im )
                       / ( den_re*den_re + den_im*den_im );
                tmp_im = ( num_im*den_re - num_re*den_im )
                       / ( den_re*den_re + den_im*den_im );

                /* z = z - Update */
                z_re = z_re - tmp_re;
                z_im = z_im - tmp_im;
            }

            root = 0;
            for ( r=0; r<3; r++ ) 
            {
                diff_re = z_re - roots[r][0];
                diff_im = z_im - roots[r][1];
                if ( sqrt(diff_re*diff_re + diff_im*diff_im) < 1.0 )
                    // fprintf ( out, "255 " );
                    #ifndef QUIET
                        Serial.print("255 ");
                    #else
                        ;
                    #endif
                else
                    // fprintf ( out, "0 " );
                    #ifndef QUIET
                        Serial.print("0 ");
                    #else
                        ;
                    #endif
            }
         }
    }
    Serial.print(" Time: ");
    Serial.println(millis() - start);
  
    // fclose ( out );
    // // exit ( EXIT_SUCCESS );

    #ifndef QUIET
        Serial.print("Finished");
    #else
        ;   
    #endif
    digitalWrite(LED_BUILTIN, HIGH);
    delay(200);
    digitalWrite(LED_BUILTIN, LOW); //   // turn the LED off by making the voltage LOW
    delay(200);
}
