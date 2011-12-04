#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>

#define MAX_DATA 512
#define MAX_ROWS 100

typedef struct Address
{
  int id;
  int set;
  char name[MAX_DATA];
  char email[MAX_DATA];
} Address;

typedef struct Database
{
  int max_data;
  int max_rows;
  Address * rows;
} Database;

typedef struct Connection
{
  FILE *file;
  Database *db;
} Connection;

void Database_close(Connection *);

void die(const char * message, Connection * conn)
{
  if( errno )
  {
    perror( message );
  }
  else
  {
    printf("ERROR: %s\n", message);
  }

  if (conn)
  {
    Database_close(conn);
  }

  exit(1);
}

void Address_print(Address * addr)
{
  printf("%d %s %s\n", addr->id, addr->name, addr->email);
}

void Database_load(Connection * conn)
{
  Database * db = conn->db;
  int rc = fread( &db->max_rows, sizeof ( int ), 1, conn->file);
  if (rc != 1) die("Failed to load database.", conn);

  rc = fread( &db->max_data, sizeof ( int ), 1, conn->file);
  if (rc != 1) die("Failed to load database.", conn);

  db->rows = malloc ( sizeof ( Address ) * db->max_rows );
  rc = fread( db->rows, sizeof ( Address ), db->max_rows, conn->file );
  if (rc != db->max_rows) die("Failed to load database.", conn);
}

Connection * Database_open(const char * filename, char mode)
{
  Connection * conn = malloc( sizeof( struct Connection ) );
  if(!conn) die("Memory error", conn);

  conn->db = malloc( sizeof ( struct Database ));
  if(!conn->db) die("Memory error", conn);

  if(mode == 'c')
  {
    conn->file = fopen( filename, "w" );
  } 
  else
  {
    conn->file = fopen( filename, "r+" );

    if(conn->file)
    {
      Database_load( conn );
    }
  }

  if(!conn->file) die("Failed to open the file", conn);

  return conn;
}

void Database_close(struct Connection * conn)
{
  if(conn)
  {
    if(conn->file) fclose(conn->file);
    if(conn->db) free(conn->db);
    free(conn);
  }
}

void Database_create(struct Connection * conn, int max_data, int max_rows)
{
  int i = 0;

  Database * db = conn->db;
  db->rows = malloc ( sizeof ( Address ) * max_rows );
  db->max_data = max_data;
  db->max_rows = max_rows;
  for (i = 0; i < max_rows; i++)
  {
    Address addr = { .id = i, .set = 0 };

    db->rows[i] = addr;
  }
}

void Database_write(struct Connection * conn)
{
  rewind(conn->file);

  Database * db = conn->db; 

  int rc = fwrite ( &db->max_rows, sizeof ( int ), 1, conn->file );
  if (rc != 1) die("Failed to write database.", conn);

  rc = fwrite ( &db->max_data, sizeof ( int ), 1, conn->file );
  if (rc != 1) die("Failed to write database.", conn);

  rc = fwrite( db->rows, sizeof( Address ), db->max_rows, conn->file );
  if (rc != db->max_rows) die("Failed to write database.", conn);

  rc = fflush(conn->file);
  if (rc == -1) die("Cannot flush database.", conn);
}

void safe_strncpy(char * dest, const char * val_to_cpy, int max_length)
{
  int val_to_cpy_len = strlen( val_to_cpy );
  if (val_to_cpy_len < max_length && ( val_to_cpy[val_to_cpy_len] == '\0') )
  {
    strncpy(dest, val_to_cpy, max_length);
  }
  else
  {
    if (max_length > 1) strncpy(dest, val_to_cpy, max_length - 2);
    dest[max_length - 1] = '\0';
  }
}

void Database_set(struct Connection * conn, int id, const char * name, const char * email)
{
  struct Address * addr = &conn->db->rows[id];

  if(addr->set) die("Already set, delete it first", conn);

  addr->set = 1;

  int max_data = conn->db->max_data;

  char test[513];
  memset(test, 'c', 513);
  safe_strncpy(addr->name, test, max_data);
  if(!addr->name) die("Name copy failed", conn);
  
  safe_strncpy(addr->email, email, MAX_DATA);
  if(!addr->email) die("Email copy failed", conn);
}


void Database_get(struct Connection * conn, int id)
{
  struct Address * addr = &conn->db->rows[id];

  if(addr->set)
  {
    Address_print(addr);
  }  
  else
  {
    die("ID is not set", conn);
  }
}

void Database_delete(struct Connection * conn, int id)
{
  struct Address addr = {.id = id, .set = 0};
  conn->db->rows[id] = addr;
}

void Database_list(struct Connection * conn)
{
  int i = 0;
  Database * db = conn->db;

  for(i = 0; i < db->max_rows; i++)
  {
    Address * cur = &db->rows[i] ;

    if(cur->set)
    {
      Address_print(cur);
    }
  }
}

int main(int argc, char *argv[])
{
  if(argc < 3)  die("USAGE: ex17 <dbfile> <action> [action params]", NULL);

  char * filename = argv[1];
  char action = argv[2][0];

  struct Connection * conn = Database_open(filename, action);
  int id = 0;

  if (argc > 3) id = atoi(argv[3]);

  if(id >= MAX_ROWS) die("There's not that many records.", conn);

  switch(action)
  {
    case 'c':
      Database_create(conn, MAX_DATA, MAX_ROWS);
      Database_write(conn);
      break;
  
    case 'g':
      if (argc != 4) die("Need an id to get", conn);

      Database_get(conn, id);
      break;

    case 's':
      if (argc != 6) die ("Need id, name, email to set", conn);

      Database_set(conn, id, argv[4], argv[5]);
      Database_write(conn);
      break;
      
    case 'd':
      if (argc != 4) die("Need id to delete", conn);

      Database_delete(conn, id);
      Database_write(conn);
      break;

    case 'l':
      Database_list(conn);
      break;

    default:
      die("Invalid action, only c (create), g (get), s (set), d (del), l (list) supported", conn);
  }

  Database_close(conn);

  return 0;
}

