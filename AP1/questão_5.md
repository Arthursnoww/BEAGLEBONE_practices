## RESPOSTA:

A.   

    gpioREG |= gpio_enabled

 

 

B.      

    if(gpioREG & gpio_direction) {
          gpio_enabled &= ~gpioREG;
    }
           

 

C.          

    gpioREG &= ~gpio_direction;

 

 


D.          
    
    gpioREG ^= gpio_level;

      
