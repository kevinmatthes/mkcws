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
    bool    license_mode    = false;
    str_t   language        = nullptr;
    str_t   path            = nullptr;
    str_t   project_name    = nullptr;

    for (int i = 0x0; i < argc; i++)
    {
        if      (string_contains (args[i], "-l", BEGIN))
            language    = string_crop (args[i], "-l", BEGIN);
        else if (string_contains (args[i], "--language=", BEGIN))
            language    = string_crop (args[i], "--language=", BEGIN);

        else if (string_contains (args[i], "-n", BEGIN))
            project_name    = string_crop (args[i], "-n", BEGIN);
        else if (string_contains (args[i], "--project-name=", BEGIN))
            project_name    = string_crop (args[i], "--project-name=", BEGIN);

        else if (string_contains (args[i], "-p", BEGIN))
            path    = string_crop (args[i], "-p", BEGIN);
        else if (string_contains (args[i], "--path=", BEGIN))
            path    = string_crop (args[i], "--path=", BEGIN);

        else if (  string_contains (args[i], "-L",                  BEGIN)
                || string_contains (args[i], "--license",           BEGIN)
                || string_contains (args[i], "-c",                  BEGIN)
                || string_contains (args[i], "--copyright",         BEGIN)
                || string_contains (args[i], "-s",                  BEGIN)
                || string_contains (args[i], "--show-copyright",    BEGIN)
                )
            license_mode    = true;
    };

    if (license_mode)
        license ();
    else if (path && project_name)
    {
        string_t language_lowered     = language ? string_lower (language)
                                                 : nullptr
                                                 ;
        string_t content              = string_join ( "{ \"folders\" : [ { \"path\" : \""
                                                    , "\", }, ], \"settings\" : [], }\n"
                                                    , path
                                                    );
        string_t workspace_identifier = language_lowered ? string_join ( language_lowered
                                                               , project_name
                                                               , "!"
                                                               )
                                                         : string_copy (project_name)
                                                         ;
        string_t workspace_name       = string_join ( workspace_identifier
                                                    , "code-workspace"
                                                    , "."
                                                    );

        FILE *workspace = fopen (workspace_name, "w");

        if (workspace != NULL)
        {
            fprintf (workspace, "%s", content);
            fclose (workspace);
            printf ( "The workspace '%s' is defined as follows:\n"
                     "%s\n"
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
        fprintf (stderr, "Arguments are missing!\n");

        if (! path)
            fprintf (stderr, "* There was no path to the project!\n");
        if (! project_name)
            fprintf (stderr, "* There was no project name!\n");
    };

    string_del (language);
    string_del (path);
    string_del (project_name);

    return 0x0;
}
