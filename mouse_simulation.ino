char Maze[9][15] = {   {'.', '-', '.', '-', '.', '-', '.', '-', '.', '-', '.', '-', '.', '-', '.'},
                       {'|', ' ', ' ', ' ', '|', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '|', ' ', '|'},
                       {'.', ' ', '.', ' ', '.', ' ', '.', ' ', '.', '-', '.', '-', '.', ' ', '.'},
                       {'|', ' ', '|', ' ', ' ', ' ', '|', ' ', '|', ' ', ' ', ' ', ' ', ' ', '|'},
                       {'.', ' ', '.', ' ', '.', '-', '.', ' ', '.', '-', '.', '-', '.', ' ', '.'},
                       {'|', ' ', '|', ' ', '|', ' ', ' ', ' ', '|', ' ', ' ', ' ', '|', ' ', '|'},
                       {'.', ' ', '.', ' ', '.', ' ', '.', ' ', '.', ' ', '.', ' ', '.', ' ', '.'},
                       {'|', ' ', '|', ' ', ' ', ' ', '|', ' ', ' ', ' ', '|', ' ', ' ', ' ', '|'},
                       {'.', '-', '.', '-', '.', '-', '.', '-', '.', '-', '.', '-', '.', '-', '.'}};
            
  char FFA[9][15] = {  {'.', '-', '.', '-', '.', '-', '.', '-', '.', '-', '.', '-', '.', '-', '.'},
                       {'|', '5', ' ', '4', ' ', '3', ' ', '2', ' ', '1', ' ', '2', ' ', '3', '|'},
                       {'.', ' ', '.', ' ', '.', ' ', '.', ' ', '.', ' ', '.', ' ', '.', ' ', '.'},
                       {'|', '4', ' ', '3', ' ', '2', ' ', '1', ' ', '0', ' ', '1', ' ', '2', '|'},
                       {'.', ' ', '.', ' ', '.', ' ', '.', ' ', '.', ' ', '.', ' ', '.', ' ', '.'},
                       {'|', '5', ' ', '4', ' ', '3', ' ', '2', ' ', '1', ' ', '2', ' ', '3', '|'},
                       {'.', ' ', '.', ' ', '.', ' ', '.', ' ', '.', ' ', '.', ' ', '.', ' ', '.'},
                       {'|', '6', ' ', '5', ' ', '4', ' ', '3', ' ', '2', ' ', '3', ' ', '4', '|'},
                       {'.', '-', '.', '-', '.', '-', '.', '-', '.', '-', '.', '-', '.', '-', '.'}};
        

        
        
//=====Declarations & Inital values=====
int x = 0;
int y = 0;
int xp = 1;//x and y positions
int yp = 7;
int i = 0;
char direc = 'N';//mouse will start off facing forward or "North"
char N_value;
char S_value;
char W_value;
char E_value;
char current_value;
int U_turn;//this will act as a marker later
int total;


//=====================
//          N
//
//   W             E
//
//          S
//=====================



//=====Print Maze Function=====
void PrintMaze()
{
  //=====Prints out the maze=====
  x = 0;
  y = 0;
  while(x < 15)//prints the array of the maze, depends on maze/array dimensions
  {
    Serial.print(Maze[y][x]);//prints to the serial monitor
    Serial.print(' ');//this first part prints data horizontally
    x++;
    if(x > 14)//gets to the end of the columns/horizontal row
    {
      Serial.print("\n");
      y++;//increments y to move to next row
      x = 0;//starts at the starting column again
      if(y > 8)//checks to see if at final row
      {
        x = 15;
      }
    }
  }
  Serial.print("\n");//new pretty line
  Serial.print("\n");
}


//=====Print FFA Function=====
void PrintFFA()//this does the same thing as the other function
//however, this prints out the maze data known by the mouse
{
  //=====Print-out the FFA=====
  x = 0;
  y = 0;
  while((x < 15) && (i < 33))
  {
    Serial.print(FFA[y][x]);//works exactly the same as before, however we're printing the FFA array
    Serial.print(' ');
    x++;
    if(x > 14)
    {
      Serial.print("\n");
      y++;
      x = 0;
      
      if(y > 8)
      {
        x = 15;
      }
    }
  }
  Serial.print("\n");
  Serial.print("\n");
}


void setup()
{
  Serial.begin(9600); // for serial monitor output
  delay(500);
  Serial.print("\n");//print data on new line
  
  
  //=====MAZE Titel=====
  Serial.print("MAZE");
  Serial.print("\n");
  PrintMaze(); //Call Print Maze Function
  
  
  //=====FFA Titel=====
  Serial.print("Fill Flood Algorithm");
  Serial.print("\n");
  current_value = FFA[yp][xp];//yp and xp were established already, we're at starting position
  PrintFFA(); //Call Print FFA Function
  FFA[yp][xp] = 'M';//M character in current position
}


void loop()
{
  while(i < 40)
  {
    N_value = 125;
    W_value = 125;
    E_value = 125;
    S_value = 125;
    
    
    if(direc == 'N')
    {
      FFA[yp-1][xp] = Maze[yp-1][xp];
      FFA[yp][xp-1] = Maze[yp][xp-1];
      FFA[yp][xp+1] = Maze[yp][xp+1];
      FFA[yp+1][xp] = Maze[yp+1][xp];
      
      
      if(FFA[yp-1][xp] == ' ')
          {N_value = FFA[yp-2][xp];}
      if(FFA[yp+1][xp] == ' ')
          {S_value = FFA[yp+2][xp];}
      if(FFA[yp][xp-1] == ' ')
          {W_value = FFA[yp][xp-2];}
      if(FFA[yp][xp+1] == ' ')
          {E_value = FFA[yp][xp+2];}
      
      
      if(N_value <= W_value && N_value <= E_value && N_value != 125)
          {direc = 'N';}
      else if(W_value <= N_value && W_value <= E_value && W_value != 125)
          {direc = 'W';}
      else if(E_value <= N_value && E_value <= W_value && E_value != 125)
          {direc = 'E';}
      else{direc = 'S';}
    }
    
    
    else if(direc == 'S')
    {
      FFA[yp+1][xp] = Maze[yp+1][xp];
      FFA[yp][xp+1] = Maze[yp][xp+1];
      FFA[yp][xp-1] = Maze[yp][xp-1];
      FFA[yp-1][xp] = Maze[yp-1][xp];
      
      
      if(FFA[yp+1][xp] == ' ')
          {S_value = FFA[yp+2][xp];}
      if(FFA[yp][xp+1] == ' ')
          {E_value = FFA[yp][xp+2];}
      if(FFA[yp][xp-1] == ' ')
          {W_value = FFA[yp][xp-2];}
      if(FFA[yp-1][xp] == ' ')
          {N_value = FFA[yp-2][xp];}
      
      
      if(S_value <= W_value && S_value <= E_value && S_value != 125)
          {direc = 'S';}
      else if(E_value <= S_value && E_value <= W_value && E_value != 125)
          {direc = 'E';}
      else if(W_value <= S_value && W_value <= E_value && W_value != 125)
          {direc = 'W';}
      else{direc = 'N';}
    }
    
    
    else if(direc == 'W')
    {
      FFA[yp+1][xp] = Maze[yp+1][xp];
      FFA[yp][xp+1] = Maze[yp][xp+1];
      FFA[yp][xp-1] = Maze[yp][xp-1];
      FFA[yp-1][xp] = Maze[yp-1][xp];
      
      
      if(FFA[yp][xp-1] == ' ')
          {W_value = FFA[yp][xp-2];}
      if(FFA[yp][xp+1] == ' ')
          {E_value = FFA[yp][xp+2];}
      if(FFA[yp-1][xp] == ' ')
          {N_value = FFA[yp-2][xp];}
      if(FFA[yp+1][xp] == ' ')
          {S_value = FFA[yp+2][xp];}
      
      
      if(W_value <= N_value && W_value <= S_value && W_value != 125)
          {direc = 'W';}
      else if(N_value <= W_value && N_value <= S_value && N_value != 125)
          {direc = 'N';}
      else if(S_value <= W_value && S_value <= N_value && S_value != 125)
          {direc = 'S';}
      else{direc = 'E';}
    }
    
    
    else if(direc == 'E')
    {
      FFA[yp+1][xp] = Maze[yp+1][xp];
      FFA[yp][xp+1] = Maze[yp][xp+1];
      FFA[yp][xp-1] = Maze[yp][xp-1];
      FFA[yp-1][xp] = Maze[yp-1][xp];
      
      
      if(FFA[yp][xp+1] == ' ')
          {E_value = FFA[yp][xp+2];}
      if(FFA[yp-1][xp] == ' ')
          {N_value = FFA[yp-2][xp];}
      if(FFA[yp+1][xp] == ' ')
          {S_value = FFA[yp+2][xp];}
      if(FFA[yp][xp-1] == ' ')
          {W_value = FFA[yp][xp-2];}
      
      
      if(E_value <= N_value && E_value <= S_value && E_value != 125)
          {direc = 'E';}
      else if(S_value <= E_value && S_value <= N_value && S_value != 125)
          {direc = 'S';}
      else if(N_value <= E_value && N_value <= S_value && N_value != 125)
          {direc = 'N';}
      else{direc = 'W';}
    }
    
    
    PrintFFA(); //Call Print FFA Function
    if (xp == 9 && yp ==3){i = 50;}

    if(i != 50)
    {
      if(direc == 'N')
      {
        if(N_value > current_value)
        {
          current_value = N_value + 1;
        }
        
        FFA[yp][xp] = current_value;
        yp = yp - 2;
      }
      
      else if(direc == 'S')
      {
        if(S_value > current_value)
        {
          current_value = S_value + 1;
        }
        
        FFA[yp][xp] = current_value;
        yp = yp + 2;
      }
      
      else if(direc == 'W')
      {
        if(W_value > current_value)
        {
          current_value = W_value + 1;
        }
        
        FFA[yp][xp] = current_value;
        xp = xp - 2;
      }
      
      else if(direc == 'E')
      {
        if(E_value > current_value)
        {
          current_value = E_value + 1;
        }
        
        FFA[yp][xp] = current_value;
        xp = xp + 2;
      }
      
      current_value = FFA[yp][xp];
      FFA[yp][xp] = 'M';
      i++;
    }
  }
  
  i = 0;
  Serial.println("==========================");
  FFA[3][9] = '0';
  delay(200);
  
  PrintFFA(); //Call Print FFA Function
  //if(direc=='N'){direc = 'S'} //might needed (change back the direction because it inverted
  //in the last process)
  Serial.println("==========================");
  i = 0;
  xp = 9;
  yp = 3;
  
  while(i < 40)
  {
    N_value = 125;
    W_value = 125;
    E_value = 125;
    S_value = 125;
    
    if(direc == 'N')
    {
      FFA[yp-1][xp] = Maze[yp-1][xp];
      FFA[yp][xp-1] = Maze[yp][xp-1];
      FFA[yp][xp+1] = Maze[yp][xp+1];
      FFA[yp+1][xp] = Maze[yp+1][xp];
      
      
      if(FFA[yp-1][xp] == ' ')
          {N_value = FFA[yp-2][xp];}
      if(FFA[yp+1][xp] == ' ')
          {S_value = FFA[yp+2][xp];}
      if(FFA[yp][xp-1] == ' ')
          {W_value = FFA[yp][xp-2];}
      if(FFA[yp][xp+1] == ' ')
          {E_value = FFA[yp][xp+2];}
      
      
      if(N_value <= W_value && N_value <= E_value && N_value != 125)
          {direc = 'N';}
      else if(W_value <= N_value && W_value <= E_value && W_value != 125)
          {direc = 'W';}
      else if(E_value <= N_value && E_value <= W_value && E_value != 125)
          {direc = 'E';}
      else{direc = 'S'; U_turn = 1;}
    }
    
    
    else if(direc == 'S')
    {
      FFA[yp+1][xp] = Maze[yp+1][xp];
      FFA[yp][xp+1] = Maze[yp][xp+1];
      FFA[yp][xp-1] = Maze[yp][xp-1];
      FFA[yp-1][xp] = Maze[yp-1][xp];
      
      
      if(FFA[yp+1][xp] == ' ')
          {S_value = FFA[yp+2][xp];}
      if(FFA[yp][xp+1] == ' ')
          {E_value = FFA[yp][xp+2];}
      if(FFA[yp][xp-1] == ' ')
          {W_value = FFA[yp][xp-2];}
      if(FFA[yp-1][xp] == ' ')
          {N_value = FFA[yp-2][xp];}
      
      
      if(S_value <= W_value && S_value <= E_value && S_value != 125)
          {direc = 'S';}
      else if(E_value <= S_value && E_value <= W_value && E_value != 125)
          {direc = 'E';}
      else if(W_value <= S_value && W_value <= E_value && W_value != 125)
          {direc = 'W';}
      else{direc = 'N'; U_turn = 1;}
    }
    
    
    else if(direc == 'W')
    {
      FFA[yp+1][xp] = Maze[yp+1][xp];
      FFA[yp][xp+1] = Maze[yp][xp+1];
      FFA[yp][xp-1] = Maze[yp][xp-1];
      FFA[yp-1][xp] = Maze[yp-1][xp];
      
      
      if(FFA[yp][xp-1] == ' ')
          {W_value = FFA[yp][xp-2];}
      if(FFA[yp][xp+1] == ' ')
          {E_value = FFA[yp][xp+2];}
      if(FFA[yp-1][xp] == ' ')
          {N_value = FFA[yp-2][xp];}
      if(FFA[yp+1][xp] == ' ')
          {S_value = FFA[yp+2][xp];}
      
      
      if(W_value <= N_value && W_value <= S_value && W_value != 125)
          {direc = 'W';}
      else if(N_value <= W_value && N_value <= S_value && N_value != 125)
          {direc = 'N';}
      else if(S_value <= W_value && S_value <= N_value && S_value != 125)
          {direc = 'S';}
      else{direc = 'E'; U_turn = 1;}
    }
    
    
    else if(direc == 'E')
    {
      FFA[yp+1][xp] = Maze[yp+1][xp];
      FFA[yp][xp+1] = Maze[yp][xp+1];
      FFA[yp][xp-1] = Maze[yp][xp-1];
      FFA[yp-1][xp] = Maze[yp-1][xp];
      
      
      if(FFA[yp][xp+1] == ' ')
          {E_value = FFA[yp][xp+2];}
      if(FFA[yp-1][xp] == ' ')
          {N_value = FFA[yp-2][xp];}
      if(FFA[yp+1][xp] == ' ')
          {S_value = FFA[yp+2][xp];}
      if(FFA[yp][xp-1] == ' ')
          {W_value = FFA[yp][xp-2];}
      
      
      if(E_value <= N_value && E_value <= S_value && E_value != 125)
          {direc = 'E';}
      else if(S_value <= E_value && S_value <= N_value && S_value != 125)
          {direc = 'S';}
      else if(N_value <= E_value && N_value <= S_value && N_value != 125)
          {direc = 'N';}
      else{direc = 'W'; U_turn = 1;}
    }
    
    
    PrintFFA(); //Call Print FFA Function
    if (xp == 1 && yp == 7){i = 50;}
    
    total = 0;
    if(N_value==125)
        {total = total + 1;}
    if(S_value==125)
        {total = total + 1;}
    if(W_value==125)
        {total = total + 1;}
    if(E_value==125)
        {total = total + 1;}
    
    if(total < 2)
    {
      U_turn = 0;
    }
    
    if(direc == 'N')
    {
      if(N_value < FFA[yp][xp] && U_turn==0)
      {
        FFA[yp-2][xp] = FFA[yp][xp] + 1;
      }
      yp = yp - 2;
    }
    
    else if(direc == 'S')
    {
      if(S_value < FFA[yp][xp] && U_turn==0)
      {
        FFA[yp+2][xp] = FFA[yp][xp] + 1;
      }
      yp = yp + 2;
    }
    
    else if(direc == 'W')
    {
      if(W_value < FFA[yp][xp] && U_turn==0)
      {
        FFA[yp][xp-2] = FFA[yp][xp] + 1;
      }
      xp = xp - 2;
    }
    
    else if(direc == 'E')
    {
      if(E_value < FFA[yp][xp] && U_turn==0)
      {
        FFA[yp][xp+2] = FFA[yp][xp] + 1;
      }
      xp = xp + 2;
    }
    
    i++;
    
  }
  
  
  Serial.println("==========================");
  i = 0;
  xp = 1;
  yp = 7;
  direc = 'N';
  FFA[yp][xp] = 'X';
  while(i < 40)
  {
    N_value = 125;
    W_value = 125;
    E_value = 125;
    S_value = 125;
    
    
    if(direc == 'N')
    {
      FFA[yp-1][xp] = Maze[yp-1][xp];
      FFA[yp][xp-1] = Maze[yp][xp-1];
      FFA[yp][xp+1] = Maze[yp][xp+1];
      FFA[yp+1][xp] = Maze[yp+1][xp];
      
      
      if(FFA[yp-1][xp] == ' ')
          {N_value = FFA[yp-2][xp];}
      if(FFA[yp+1][xp] == ' ')
          {S_value = FFA[yp+2][xp];}
      if(FFA[yp][xp-1] == ' ')
          {W_value = FFA[yp][xp-2];}
      if(FFA[yp][xp+1] == ' ')
          {E_value = FFA[yp][xp+2];}
      
      
      if(N_value <= W_value && N_value <= E_value && N_value != 125)
          {direc = 'N';}
      else if(W_value <= N_value && W_value <= E_value && W_value != 125)
          {direc = 'W';}
      else if(E_value <= N_value && E_value <= W_value && E_value != 125)
          {direc = 'E';}
      else{direc = 'S';}
    }
    
    
    else if(direc == 'S')
    {
      FFA[yp+1][xp] = Maze[yp+1][xp];
      FFA[yp][xp+1] = Maze[yp][xp+1];
      FFA[yp][xp-1] = Maze[yp][xp-1];
      FFA[yp-1][xp] = Maze[yp-1][xp]; 
      
      
      if(FFA[yp+1][xp] == ' ')
          {S_value = FFA[yp+2][xp];}
      if(FFA[yp][xp+1] == ' ')
          {E_value = FFA[yp][xp+2];}
      if(FFA[yp][xp-1] == ' ')
          {W_value = FFA[yp][xp-2];}
      if(FFA[yp-1][xp] == ' ')
          {N_value = FFA[yp-2][xp];}
      
      
      if(S_value <= W_value && S_value <= E_value && S_value != 125)
          {direc = 'S';}
      else if(E_value <= S_value && E_value <= W_value && E_value != 125)
          {direc = 'E';}
      else if(W_value <= S_value && W_value <= E_value && W_value != 125)
          {direc = 'W';}
      else{direc = 'N';}
    }
    
    
    else if(direc == 'W')
    {
      FFA[yp+1][xp] = Maze[yp+1][xp];
      FFA[yp][xp+1] = Maze[yp][xp+1];
      FFA[yp][xp-1] = Maze[yp][xp-1];
      FFA[yp-1][xp] = Maze[yp-1][xp];
      
      
      if(FFA[yp][xp-1] == ' ')
          {W_value = FFA[yp][xp-2];}
      if(FFA[yp][xp+1] == ' ')
          {E_value = FFA[yp][xp+2];}
      if(FFA[yp-1][xp] == ' ')
          {N_value = FFA[yp-2][xp];}
      if(FFA[yp+1][xp] == ' ')
          {S_value = FFA[yp+2][xp];}
      
      
      if(W_value <= N_value && W_value <= S_value && W_value != 125)
          {direc = 'W';}
      else if(N_value <= W_value && N_value <= S_value && N_value != 125)
          {direc = 'N';}
      else if(S_value <= W_value && S_value <= N_value && S_value != 125)
          {direc = 'S';}
      else{direc = 'E';}
    }
    
    
    else if(direc == 'E')
    {
      FFA[yp+1][xp] = Maze[yp+1][xp];
      FFA[yp][xp+1] = Maze[yp][xp+1];
      FFA[yp][xp-1] = Maze[yp][xp-1];
      FFA[yp-1][xp] = Maze[yp-1][xp];
      
      
      if(FFA[yp][xp+1] == ' ')
          {E_value = FFA[yp][xp+2];}
      if(FFA[yp-1][xp] == ' ')
          {N_value = FFA[yp-2][xp];}
      if(FFA[yp+1][xp] == ' ')
          {S_value = FFA[yp+2][xp];}
      if(FFA[yp][xp-1] == ' ')
          {W_value = FFA[yp][xp-2];}
      
      
      if(E_value <= N_value && E_value <= S_value && E_value != 125)
          {direc = 'E';}
      else if(S_value <= E_value && S_value <= N_value && S_value != 125)
          {direc = 'S';}
      else if(N_value <= E_value && N_value <= S_value && N_value != 125)
          {direc = 'N';}
      else{direc = 'W';}
    }
    
    //PrintFFA(); //Call Print FFA Function
    //if (xp == 9 && yp == 3){i = 50;}
    if(i != 50)
    {
      if(direc == 'N')
      {
        //FFA[yp][xp] = 'X';
        yp = yp - 2;
      }
      
      else if(direc == 'S')
      {
        //FFA[yp][xp] = 'X';
        yp = yp + 2;
      }
      
      else if(direc == 'W')
      {
        //FFA[yp][xp] = 'X';
        xp = xp - 2;
      }
      
      else if(direc == 'E')
      {
        //FFA[yp][xp] = 'X';
        xp = xp + 2;
      }
      
      //current_value = FFA[yp][xp];
      FFA[yp][xp] = 'X';
      i++;
      PrintFFA(); //Call Print FFA Function
      
      if (xp == 9 && yp == 3){i = 50;}
    }
  }
  
  i = 0;
 
  PrintFFA(); //Call Print FFA Function

  PrintFFA(); //Call Print FFA Function
  while(1);
}

