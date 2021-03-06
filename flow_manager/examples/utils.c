/*
 * Author: Yasunobu Chiba
 *
 * Copyright (C) 2011 NEC Corporation
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License, version 2, as
 * published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License along
 * with this program; if not, write to the Free Software Foundation, Inc.,
 * 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
 */


#include "libpath.h"
#include "trema.h"


void
dump_hop( const hop *h ) {
  info( "Hop: datapath_id = %#" PRIx64 ", in_port = %u, out_port = %u, extra_actions = %p.",
        h->datapath_id, h->in_port, h->out_port, h->extra_actions );
}


void
dump_path( const path *p ) {
  char match_string[ 256 ];
  match_to_string( &p->match, match_string, sizeof( match_string ) );

  info( "Path: match = [%s], priority = %u, idle_timeout = %u, hard_timeout = %u, n_hops = %d, hops = %p.",
        match_string, p->priority, p->idle_timeout, p->hard_timeout, p->n_hops, p->hops );
  if ( p->n_hops > 0 && p->hops != NULL ) {
    list_element *e = p->hops;
    while ( e != NULL ) {
      dump_hop( e->data );
      e = e->next;
    }
  }
}


const char *
status_to_string( int status ) {
  switch ( status ) {
    case SETUP_SUCCEEDED:
      return "succeeded";
    break;
    case SETUP_CONFLICTED_ENTRY:
      return "conflicted entry";
    break;
    case SETUP_SWITCH_ERROR:
      return "switch error";
    break;
    default:
    break;
  }

  return "undefined";
}


const char *
reason_to_string( int reason ) {
  switch ( reason ) {
    case TEARDOWN_TIMEOUT:
      return "timeout";
    break;
    case TEARDOWN_MANUALLY_REQUESTED:
      return "manually requested";
    break;
    default:
    break;
  }

  return "undefined";
}


/*
 * Local variables:
 * c-basic-offset: 2
 * indent-tabs-mode: nil
 * End:
 */
