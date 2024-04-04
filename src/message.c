#include "message.h"

// you need to have a structure in place that represents messages. Messages have a type and other 
// information, like chat_node information and text that represents a NOTE. Here, you will also 
// have code in place that handles messages, like sending and receiving them. Again, this code 
// needs to be OUTLINED.

// Function that accepts a Note and sets its Type
void setNoteType( Message note )
   {
    // cast the note inside to an int
    // to read the TYPE it is
    switch( (int)note.note )
      {
       case JOIN:
       note.type = JOIN;
         break;

       case LEAVE:
       note.type = LEAVE;
         break;

       case SHUTDOWN:
       note.type = SHUTDOWN;
         break;

       case SHUTDOWN_ALL:
       note.type = SHUTDOWN_ALL;
         break;

       case JOINING:
       note.type = JOINING;
         break;

       case LEFT:
       note.type = LEFT;
         break;
       
       // Otherwise, assume it is a generic NOTE
       default:
       note.type = NOTE;

      }
   }