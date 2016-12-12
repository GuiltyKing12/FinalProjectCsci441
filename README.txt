Brandon Her - bher@mines.edu
Rouge One Star Lords

Final Project - Keys to the Kingdom

Description: This is a basic simulation of the solar system. By controlling a space ship one can fly through and see the eight planets (pluto ain't a planet anymore) and the sun. There is an asteroid belt and the sun. There are baisc collisons as well.

Instruction:
  Run: enter in './keysToTheKingdom'
  
  Controls:
            'w' - moves spaceship forward
            'a' - moves spaceship left
            's' - moves spaceship backwards
            'd' - moves spaceship right
            'e' - does warp jump

            'q' or 'esc' - quits program
            
            'p' - pauses the solar system
            'r' - resets the spaceship in case of destruction

            camera is automatically set to arc ball intially
            right click brings up menu to change camera type

            arcball - click drag to move around space ship
                    - ctrl click drag horiztonally to zoom

            free cam - click drag to change heading
                     - 'i' to move forward
                     - 'k' to move backwards

  Compile:
          To compile run make

  Bugs/Notes:
          - going backwards into a planet can do wonky things sometimes
          - asteroid hitbox is kinda weird, sometimes hits

  File Format:
          - we hard coded the files because it reads from many different types, can be set to read, but here
            are the file types

          Main solarsytem text
          <number of bodies>
          <S for sun> <radius> <x> <y> <z> <revolution>
          <P for planet> <radius> <x> <y> <z> <revolution> <planet texture> <1 ring planet> <ring texture> <ring radius> <bez control points> <speed>
                                                                            <0 non ring planet> <bez control ponts><speed>
          <A for asteroid> <size> <radius> <angle> <speed> <obj file>

  Distribution of Work:
    Brandon:
      - Solar System Class
      - Skybox
      - spaceship
      - planet and sun 
      - all shader programs
      - particles systems
      - some of the collsions
    
    Kento
      - Asteroid
      - asteroid belt
      - collisons
      - skybox
    
    Kito
      - Planet orbiting path
      - bez/track class
      - planet movement
      - speed control

    32+ hours

  Lab help: 10

  Fun: 10
