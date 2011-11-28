#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <string.h>

// storage for a user defined data type
struct Person 
{
  // storage for a c-string
  char * name;
  //storage for an int
  int age;
  //storage for an int
  int height;
  //storage for an int
  int weight;
};

// method that creates a Person struct
struct Person Person_create(char * name, int age, int height, int weight)
{
  // allocates a block of memory to the heap that is the size of a Person
  struct Person who;
  // asserts that the malloc function did not return NULL
  // assigns a complete copy of the value pointed to by name into the name field in the person struct
  who.name = strdup(name);
  // assigns an int to the age value in the person struct
  who.age = age;
  // assigns an int to the height value in the person struct
  who.height = height;
  // assigns an int to the weight value in the person struct
  who.weight = weight;

  // returns an initialized Person struct
  return who;
}

//function that deletes a Person struct
void Person_destroy(struct Person who)
{
  // releases the c string in the Person struct
  free(who.name);
  // releases the rest of the memory allocated to the Person struct
}

// Function that prints out the values of a Person struct
void Person_print(struct Person who)
{
  // Prints the name string in the Person struct
  printf("Name: %s\n", who.name);
  // Prints the age in the Person struct
  printf("\tAge: %d\n", who.age);
  // Prints the height in the Person struct
  printf("\tHeight: %d\n", who.height);
  // Prints the weight in the Person struct
  printf("\tWeight: %d\n", who.weight);
}

// Runs the program
int main(int argc, char *argv[])
{
  // Creates a person with the appropriate values initialized
  struct Person joe = Person_create("Joe Alex", 32, 64, 140);
  // Creates a person with the appropriate values initialized
  struct Person frank = Person_create("Frank Blank", 20, 72, 180);

  // prints the address of Joe
  printf("Joe is at memory location %p:\n", &joe);
  // prints Joe's attributes 
  Person_print(joe);

  // prints the address of Frank
  printf("Frank is at memory location %p:\n", &frank);
  // prints Frank's attributes 
  Person_print(frank);

  // adds 20 to the age value in the Joe struct
  joe.age += 20;
  // subtracts 2 from the height value in the Joe struct
  joe.height -= 2;
  // adds 40 to the weight value in the Joe struct
  joe.weight += 40;
  // Prints the modified Joe struct
  Person_print(joe);

  // Updates the frank struct
  frank.age += 20;
  frank.weight += 20;
  Person_print(frank);

  // Cleans up the joe and frank structs
  Person_destroy(joe);
  Person_destroy(frank);

  return 0;
}
