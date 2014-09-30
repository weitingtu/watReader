/*
 * watReader.cpp
 *
 *  Created on: 2014/10/1
 *      Author: weitingtu
 */
#include "watReader.h"
#include <stdlib.h>
#include <iostream>

WATParser::WATParser():
  _watManager()
{
}

WATParser::~WATParser()
{
}

void
WATParser::parse(const string& line, const int nb)
{
  if(1 == nb) {
    // ignore
  } else if (2 == nb) {
    parseHeader2(line);
  } else if (3 == nb) {
    // ignore
  } else if (4 == nb) {
    // ignore
  } else if (5 == nb) {
    parseHeader5(line);
    // ignore
  } else if (6 == nb) {
    // ignore
  } else {
    parseDataValue(line);
  }
}

// parse header line #2
void
WATParser::parseHeader2(const string& line)
{
  size_t pos = 0;
  pos = line.find(' ', pos + 1);
  pos = line.find(' ', pos + 1);
  pos = line.find(' ', pos + 1);
  string token = line.substr(pos, line.size() - pos);
  watManager().setLotID(token);
}

void
WATParser::parseHeader5(const string& line)
{
  size_t pos = 7;
  size_t len = 18;
  size_t space = 2;
  while(pos < line.size()) {
    string v = parseString(line, pos, len, space);
    watManager().addField(v);
  }
}

void
WATParser::parseDataValue(const string& line)
{
  size_t pos = 0;
  size_t len = 2;
  size_t space = 2;
  int waferID = parseInt(line, pos, len, space);
  if(0 == waferID) {
    // not data value
    return;
  }

  len = 1;
  space = 2;
  int siteID = parseInt(line, pos, len, space);

  WAT w = WAT(waferID, siteID);
  len = 14;
  space = 6;
  while(pos < line.size()) {
    double v = parseDouble(line, pos, len, space);
    w.addParameter(v);
  }

  //watList().push_back(w);
  watManager().addWAT(w);
}

int
WATParser::parseInt(const string& line, size_t& pos, const size_t& len, const size_t& space)
{
  string token = line.substr(pos, len);
  int v = atoi(token.c_str());
  pos = pos + len + space;
  return v;
}

double
WATParser::parseDouble(const string& line, size_t& pos, const size_t& len, const size_t& space)
{
  string token = line.substr(pos, len);
  double v = atof(token.c_str());
  pos = pos + len + space;
  return v;
}

string
WATParser::parseString(const string& line, size_t& pos, const size_t& len, const size_t& space)
{
  string token = line.substr(pos, len);
  pos = pos + len + space;
  return token;
}





