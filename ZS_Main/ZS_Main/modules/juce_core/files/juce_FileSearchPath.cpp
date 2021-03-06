/*
  ==============================================================================

   This file is part of the JUCE library.
   Copyright (c) 2016 - ROLI Ltd.

   Permission is granted to use this software under the terms of the ISC license
   http://www.isc.org/downloads/software-support-policy/isc-license/

   Permission to use, copy, modify, and/or distribute this software for any
   purpose with or without fee is hereby granted, provided that the above
   copyright notice and this permission notice appear in all copies.

   THE SOFTWARE IS PROVIDED "AS IS" AND ISC DISCLAIMS ALL WARRANTIES WITH REGARD
   TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF MERCHANTABILITY AND
   FITNESS. IN NO EVENT SHALL ISC BE LIABLE FOR ANY SPECIAL, DIRECT, INDIRECT,
   OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES WHATSOEVER RESULTING FROM LOSS OF
   USE, DATA OR PROFITS, WHETHER IN AN ACTION OF CONTRACT, NEGLIGENCE OR OTHER
   TORTIOUS ACTION, ARISING OUT OF OR IN CONNECTION WITH THE USE OR PERFORMANCE
   OF THIS SOFTWARE.

   -----------------------------------------------------------------------------

   To release a closed-source product which uses other parts of JUCE not
   licensed under the ISC terms, commercial licenses are available: visit
   www.juce.com for more information.

  ==============================================================================
*/

FileSearchPath::FileSearchPath() {}
FileSearchPath::~FileSearchPath() {}

FileSearchPath::FileSearchPath (const String& path)
{
    init (path);
}

FileSearchPath::FileSearchPath (const FileSearchPath& other)
   : directories (other.directories)
{
}

FileSearchPath& FileSearchPath::operator= (const FileSearchPath& other)
{
    directories = other.directories;
    return *this;
}

FileSearchPath& FileSearchPath::operator= (const String& path)
{
    init (path);
    return *this;
}

void FileSearchPath::init (const String& path)
{
    directories.clear();
    directories.addTokens (path, ";", "\"");
    directories.trim();
    directories.removeEmptyStrings();

    for (int i = directories.size(); --i >= 0;)
        directories.set (i, directories[i].unquoted());
}

int FileSearchPath::getNumPaths() const
{
    return directories.size();
}

File FileSearchPath::operator[] (const int index) const
{
    return File (directories [index]);
}

String FileSearchPath::toString() const
{
    StringArray directories2 (directories);
    for (int i = directories2.size(); --i >= 0;)
        if (directories2[i].containsChar (';'))
            directories2.set (i, directories2[i].quoted());

    return directories2.joinIntoString (";");
}

void FileSearchPath::add (const File& dir, const int insertIndex)
{
    directories.insert (insertIndex, dir.getFullPathName());
}

bool FileSearchPath::addIfNotAlreadyThere (const File& dir)
{
    for (int i = 0; i < directories.size(); ++i)
        if (File (directories[i]) == dir)
            return false;

    add (dir);
    return true;
}

void FileSearchPath::remove (const int index)
{
    directories.remove (index);
}

void FileSearchPath::addPath (const FileSearchPath& other)
{
    for (int i = 0; i < other.getNumPaths(); ++i)
        addIfNotAlreadyThere (other[i]);
}

void FileSearchPath::removeRedundantPaths()
{
    for (int i = directories.size(); --i >= 0;)
    {
        const File d1 (directories[i]);

        for (int j = directories.size(); --j >= 0;)
        {
            const File d2 (directories[j]);

            if ((i != j) && (d1.isAChildOf (d2) || d1 == d2))
            {
                directories.remove (i);
                break;
            }
        }
    }
}

void FileSearchPath::removeNonExistentPaths()
{
    for (int i = directories.size(); --i >= 0;)
        if (! File (directories[i]).isDirectory())
            directories.remove (i);
}

int FileSearchPath::findChildFiles (Array<File>& results,
                                    const int whatToLookFor,
                                    const bool searchRecursively,
                                    const String& wildCardPattern) const
{
    int total = 0;

    for (int i = 0; i < directories.size(); ++i)
        total += operator[] (i).findChildFiles (results,
                                                whatToLookFor,
                                                searchRecursively,
                                                wildCardPattern);

    return total;
}

bool FileSearchPath::isFileInPath (const File& fileToCheck,
                                   const bool checkRecursively) const
{
    for (int i = directories.size(); --i >= 0;)
    {
        const File d (directories[i]);

        if (checkRecursively)
        {
            if (fileToCheck.isAChildOf (d))
                return true;
        }
        else
        {
            if (fileToCheck.getParentDirectory() == d)
                return true;
        }
    }

    return false;
}
