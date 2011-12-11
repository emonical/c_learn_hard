#include <stdio.h>
#include <stdlib.h>

// This is so so so not a safe stack
// Quick proof of concept. Refactor later.

typedef struct Item
{
  int value;
  struct Item * prev_item;
} Item;

typedef struct Stack
{
  Item * top;
} Stack; 

Stack * create_stack()
{
  Stack * stack = malloc ( sizeof ( Stack )); 
  stack->top = NULL;
  return stack;
}

Item * create_item( int value, Item * prev_item )
{
  Item * item = malloc ( sizeof ( Item ));
  item->value = value;
  item->prev_item = prev_item;
  return item;
}

void add_item_to_stack( Stack * stack, int value)
{
  Item * item = create_item( value, stack->top );
  stack->top = item;
}

int pop_stack ( Stack * stack )
{
  Item * top_item = stack->top;
  int ret_val = top_item->value;
  
  stack->top = top_item->prev_item;

  free(top_item);

  return ret_val;
}

int main(int argc, char *argv[])
{
  Stack * s = create_stack();
  add_item_to_stack( s, 1 );
  add_item_to_stack( s, 3 );
  
  int top_val = pop_stack ( s );
  printf("Top value on the stack is: %d\n", top_val);
  top_val = pop_stack ( s );
  top_val = pop_stack ( s );
  printf("The second value on the stack is: %d\n", top_val);
  return 0;
}
