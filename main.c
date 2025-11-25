#include "singly_linked_list.h"
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define TRACK_TITLE_SIZE 60

#define PLAYLIST_IN_PATH "playlist.txt"
#define PLAYLIST_OUT_PATH "playlist-out.txt"
// To avoid unnecessary complexity, we fix the filenames instead of getting them
// through runtime parameters.

typedef char Data[TRACK_TITLE_SIZE];
Node *playlist;

/// Removes trailing newline from the line, if it exists.
/// Note: Some lines may not have a newline, e.g., last line in a file,
/// therefore we have to check for presence.
char *remove_newline_if_exists(char *line) {
  // YOUR CODE HERE
  // i check for newline at the end of the string, if there is a newline
  // i replace it with the null terminator.
  size_t len = strlen(line);
  if (len > 0 && line[len -1] == '\n') {
    line[len -1] = '\0';
  }
  return line;
}

/// Reads lines from at `filename`, creates a node for each line and inserts
/// nodes to `list`.
Node **load_file(const char *playlist, Node **list) {
  // Open the file and assign to stream `f`
  // YOUR CODE HERE
  // if open the platlist file 
  FILE *f = fopen(playlist, "r");
  if (!f) {
    perror(PLAYLIST_IN_PATH);
    exit(EXIT_FAILURE);
  }
  char line[TRACK_TITLE_SIZE];

  while (
      // Read one line from the stream
      // YOUR CODE HERE
      // using the fgets function to read a line from the file
      fgets(line,TRACK_TITLE_SIZE, f)
  ) {
    remove_newline_if_exists(line);

    Node *new_node = (Node *)malloc(sizeof(Node));
    new_node->next = nullptr;
    Data *data = (Data *)malloc(sizeof(Data));
    new_node->data = data;

    // Copy line to `new_node` and append `new_node` to `list`
    // YOUR CODE HERE
    // using the strcpy function to copy and paste the copied line into new_node
    strcpy((char *)new_node->data, line);
    // using geckos function insert_at to append the new_node to the list
    insert_at(list, list_len(*list), new_node);
  }
  fclose(f);
  return list;
}

/// Saves `list` contents to the file at `filename`.
void save_file(const char *playlist, Node *list) {
  // Open file
  // YOUR CODE HERE
  FILE *f = fopen(playlist, "w");

  // Move through the list and save the tracks to the file
  // Note: You have to cast the data to print the track to the file as follows:
  // (char *)current->data
  // Because current->data is a pointer to everything (void*).
  Node *current = list;
  // YOUR CODE HERE
  while (current) {
    fprintf(f, "%s\n", (char *)current->data);
    current = current->next;
  }

  fclose(f);
  //// END SOLUTION
}

void print_tracks(const Node *const playlist) {
  const Node *current = playlist;
  for (size_t i = 1; current; i++, current = current->next)
    printf("%2ld: %s\n", i, (char *)current->data);
}

int main() {
  printf("the playlist before i insert Tarken in it %s\n", PLAYLIST_IN_PATH);
  load_file(PLAYLIST_IN_PATH, &playlist);
  print_tracks(playlist);

  // Deletion
  size_t node_index_to_del = 4;
  free(delete_at(&playlist, node_index_to_del));

  // Insertion
  // change the name of the song to be inserted because it kept showing orange markers
  // that were distracting
  Node node = {.data = "Metallica 'Enter Sandman' ", .next = nullptr};
  insert_at(&playlist, 3, &node);

  save_file(PLAYLIST_OUT_PATH, playlist);

  // added this line just to visualise the changes that was made from the input file
  // to the output file
  playlist = NULL;
  printf("\nthe playlist after i insert Tarken in it");
  printf("\n%s\n", PLAYLIST_OUT_PATH);
  load_file(PLAYLIST_OUT_PATH, &playlist);
  print_tracks(playlist);
}