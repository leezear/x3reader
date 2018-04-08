//
// Created by leezear on 18-4-8.
//

#ifndef READER_BMFILEPARSER_H
#define READER_BMFILEPARSER_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <string>
#include <iostream>
#include <err.h>

#include "libxml/SAX2.h"
#include "libxml/xmlstring.h"

using namespace std;

string _bm_path;
bool hasfile;

void startElement(void *user_data, const xmlChar *name, const xmlChar **attrs) {
    if (!xmlStrcmp(name, (const xmlChar *) "BMFile")) {
        hasfile = true;
    }
}

void endElement(void *parser, const xmlChar *name) {
    if (!xmlStrcmp(name, BAD_CAST "BMFile")) {
        hasfile = false;
    }
}

static void OnCharacters(void *ctx, const xmlChar *ch, int len) {
    if (hasfile) {
        _bm_path = string(ch, ch + len);
    }
}

bool FindBMPath(const string& file_name) {
//    errno err;
    FILE *f = fopen(file_name.c_str(), "rb");
//    err = fopen(&f, file_name.c_str(), "rb");
    char chars[1024];
    int res = fread(chars, 1, 4, f);
    if (res <= 0) {
        return false;
    }

    xmlInitParser();

    xmlSAXHandler SAXHander;
    memset(&SAXHander, 0, sizeof(xmlSAXHandler));
    SAXHander.initialized = XML_SAX2_MAGIC;
    SAXHander.startElement = startElement;
    SAXHander.endElement = endElement;
    SAXHander.characters = OnCharacters;

    xmlParserCtxtPtr ctxt = xmlCreatePushParserCtxt(&SAXHander, NULL, chars,
                                                    res, NULL);

    while ((res = fread(chars, 1, sizeof(chars) - 1, f)) > 0) {
        if (xmlParseChunk(ctxt, chars, res, 0)) {
            xmlParserError(ctxt, "xmlParseChunk");
            return false;
        }
    }
    xmlParseChunk(ctxt, chars, 0, 1);

    xmlFreeParserCtxt(ctxt);
    xmlCleanupParser();
    fclose(f);
    return true;
}

#endif //READER_BMFILEPARSER_H
