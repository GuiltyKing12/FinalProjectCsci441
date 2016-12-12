Jose "Kito" Acosta - jacosta@mymail.mines.edu
Guild: Rogue One Star Lords
Guild Members: 	Brandon Her (Turning in the Code)
				Kento Okamoto

Final Project - Keys to the Kingdom

Description: This is a basic simulation of the Solar System. By controlling a spaceship, one can fly through the Solar System and see the eight planets (Pluto ain't a planet anymore). There is also an asteroid belt and the Sun. There are basic collisions as well.

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

            camera is automatically set to arc ball initially
            right click brings up menu to change camera type

            arcball - click drag to move around space ship
                    - ctrl click drag horizontally to zoom

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

          Main solarsystem text
          <number of bodies>
          <S for sun> <radius> <x> <y> <z> <revolution>
          <P for planet> <radius> <x> <y> <z> <revolution> <planet texture> <1 ring planet> <ring texture> <ring radius> <bez control points> <speed>
                                                                            <0 non ring planet> <bez control points><speed>
          <A for asteroid> <min radius> <max radius> <min size> <max size> <Number of Asteroids> <speed>

  Distribution of Work:
    Brandon:
      - Solar System Class
      - Skybox
      - spaceship
      - planet and sun 
      - all shader programs
      - particles systems
      - some of the collisions
    
    Kento
      - Asteroid
      - asteroid belt
      - collisions
      - skybox
    
    Kito
      - Planet orbiting path
      - bez/track class
      - planet movement
      - speed control

    32+ hours

  Lab help: 10

  Fun: 10
