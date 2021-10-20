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
#include <stdlib.h>



/**
 * Type definitions.
 */

typedef unsigned long long int natural_t;
typedef char *                 str_t;
typedef char * const           string_t;



/**
 * Function declarations of local auxillary functions.
 */

natural_t len     (const string_t  self);
str_t     join    (const string_t  self, const string_t other, const string_t by);
void      license (void);
str_t     lower   (const string_t  self);
str_t     string  (const natural_t size);



/**
 * Local auxillary functions.
 */

str_t join (const string_t self, const string_t other, const string_t by)
{
    natural_t counter = 0ULL;
    string_t  ret     = string (len (self) + len (other) + len (by) + 0x1);

    for (natural_t i = 0ULL; self[i];  counter++, i++)
        ret[counter] = self[i];

    for (natural_t i = 0ULL; by[i];    counter++, i++)
        ret[counter] = by[i];

    for (natural_t i = 0ULL; other[i]; counter++, i++)
        ret[counter] = other[i];

    return ret;
}

natural_t len (const string_t self)
{
    natural_t ret = 0ULL;
    for (ret = 0ULL; self[ret]; ret++);
    return ret;
}

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

str_t lower (const string_t self)
{
    const int offset = 'a' - 'A';
    string_t  ret = string (len (self) + 0x1);

    for (natural_t i = 0ULL; self[i]; i++)
        if ('A' <= self[i] && self[i] <= 'Z')
            ret[i] = self[i] + offset;
        else
            ret[i] = self[i];

    return ret;
}

inline str_t string (const natural_t size)
{
    return (str_t) calloc (size, sizeof (char));
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

        string_t language_lowered     = lower (language);
        string_t content              = join ( "{ \"folders\" : [ { \"path\" : \""
                                             , "\", }, ], \"settings\" : [], }\n"
                                             , path
                                             );
        string_t workspace_identifier = join ( language_lowered
                                             , project_name
                                             , "!"
                                             );
        string_t workspace_name       = join ( workspace_identifier
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

        free (content);
        free (language_lowered);
        free (workspace_identifier);
        free (workspace_name);
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
