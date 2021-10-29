/**
 * main.c : main source file of `mkcws'.
 *
 * See `LICENSE' for full license.
 * See `README.md' for project details.
 */

/**
 * Copyright (C) 2021 Kevin Matthes
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
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

/******************************************************************************/

/**
 * Includes.
 */

#include <stdio.h>
#include "libstring.h"



/**
 * Function declarations of local auxillary functions.
 */

void    license (void);



/**
 * Local auxillary functions.
 */

inline void license (void)
{
    printf ("Copyright (C) 2021 Kevin Matthes\n"
            "\n"
            "This program is free software; you can redistribute it and/or modify\n"
            "it under the terms of the GNU General Public License as published by\n"
            "the Free Software Foundation; either version 2 of the License, or\n"
            "(at your option) any later version.\n"
            "\n"
            "This program is distributed in the hope that it will be useful,\n"
            "but WITHOUT ANY WARRANTY; without even the implied warranty of\n"
            "MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the\n"
            "GNU General Public License for more details.\n"
            "\n"
            "You should have received a copy of the GNU General Public License along\n"
            "with this program; if not, write to the Free Software Foundation, Inc.,\n"
            "51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.\n"
           );

    return;
}



/**
 * The main function.
 */

int main (int argc, char **args)
{
    if (argc == 0x4)
    {
        const string_t language     = args[0x1];
        const string_t path         = args[0x3];
        const string_t project_name = args[0x2];

        string_t language_lowered     = string_lower (language);
        string_t content              = string_join ( "{ \"folders\" : [ { \"path\" : \""
                                                    , "\", }, ], \"settings\" : [], }\n"
                                                    , path
                                                    );
        string_t workspace_identifier = string_join ( language_lowered
                                                    , project_name
                                                    , "!"
                                                    );
        string_t workspace_name       = string_join ( workspace_identifier
                                                    , "code-workspace"
                                                    , "."
                                                    );

        FILE *workspace = fopen (workspace_name, "w");

        if (workspace != NULL)
        {
            fprintf (workspace, "%s", content);
            fclose (workspace);
            printf ( "Workspace created successfully by using:\n"
                     "- Language:     %s\n"
                     "- Project name: %s\n"
                     "- Path:         %s\n"
                     "\n"
                     "The workspace '%s' is defined as follows:\n"
                     "%s\n"
                   , language
                   , project_name
                   , path
                   , workspace_name
                   , content
                   );
        }
        else
            fprintf (stderr, "The workspace could not be created properly!\n");

        string_del (content);
        string_del (language_lowered);
        string_del (workspace_identifier);
        string_del (workspace_name);
    }
    else
    {
        fprintf ( stderr
                , "The argument count is unexpected!\n"
                  "These arguments were detected:\n"
                );

        for (int i = 0x0; i < argc; i++)
            fprintf (stderr, "- %s\n", args[i]);
    };

    printf ("\n");
    license ();

    return 0x0;
}
