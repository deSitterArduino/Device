//**************************************************************************************************
//    sd_card.cpp -
//
//    Copyright 2018, Greg Boucher, All rights reserved.
//**************************************************************************************************

#include "sd_card.h"
#include "errorHandler.h"

namespace device_lib {

SdCard::SdCard()
    :_path{"file.txt"}
{
    if (!_sd.begin(10)) reportError("error SD begin");
}

int SdCard::fetchNumEntries(SdFile& file) {
    Serial.println(F("(DEBUG) Entered fetchNumEntries"));
    if (file.fileSize() == 0) {     //file has just been created
        Serial.println(F("(DEBUG) FileSize = 0"));
        return 0;
    } else {
        char c = ' ';
        String num = " ";
        file.rewind();
        while ((c = file.read()) >= 0) {
            Serial.println(c);
            if (!((c == '\r') | (c == '\n'))) {
                num += c;
            } else {
                break;
            }
        }
        Serial.print(F("(DEBUG) Num to Int: "));
        Serial.println(num.toInt());
        return num.toInt();
    }
}

void SdCard::writeNumEntries(SdFile& file, int n) {
    Serial.println(F("(DEBUG) Entered writeNumEntries"));
    file.rewind();
    String header = String(n);
    Serial.print(F("(DEBUG) Current header before append: "));
    Serial.println(header);
    byte delta = headerSize - header.length();
    for (int i = 0; i < delta; ++i) {
        header += '\0';
    }
    Serial.print(F("DEBUG) Header after append: "));
    Serial.println(header);
    header += '\r';
    header += '\n';
    file.print(header);
}

void SdCard::appendEntry(String date, String barcode) {
    SdFile file(_path, O_RDWR | O_CREAT);
    if (file.isOpen()) {
        int entries = fetchNumEntries(file);
        writeNumEntries(file, ++entries);
        file.seekEnd();
        file.print(date);
        file.write(" ");
        file.println(barcode);
        file.close();
    } else {
        reportError("error opening file to append");
    }

}

void SdCard::deleteFile() {
    if (_sd.exists(_path)) {
        SdFile file(_path, O_RDWR);
        file.remove();
        file.close();
        Serial.print("(DEBUG) Deleted");
    } else {
        reportError("error deleting, file does not exist");
    }
}

void SdCard::readBack() {
    SdFile file(_path, O_RDWR);
    for (int i = -10; i < 0; ++i) {
        file.seekEnd(i);
        Serial.write(file.read());
    }
}

void SdCard::readFile() {
    char c = ' ';
    SdFile file(_path, O_READ);
    if (file.isOpen()) {
        while ((c = file.read()) >= 0) {  //print contents
            Serial.print(c, DEC);
            Serial.print(" ");
            Serial.print(c);
            Serial.println(", ");
        }
    file.close();
    } else {
        reportError("error opening file to read");
    }
}






void SdCard::deleteEntry(int n) {
    char line[25];
    int c = 0;
    int i = 1;
    SdFile file("testA.txt", O_READ);
    if (!file.isOpen()) {
        Serial.println(F("Error opening file"));
    }
    while ((c = file.read()) >= 0) {  //print contents
        Serial.print(c, DEC);
        Serial.print(" ");
        Serial.print(c);
        Serial.print(", ");
    }
    file.rewind();
    SdFile wFile("testwrite.txt", O_RDWR | O_CREAT);
    if (!wFile.isOpen()) {
        Serial.println(F("Error opening wFile"));
    }
    while (file.fgets(line, sizeof(line))) {
        if (!(n == i)) {
            Serial.print("ABABABABA");
            wFile.println(line);
        }
        ++i;
    }
    file.close();
    wFile.rewind();
    Serial.println(F("OUTPUT:"));
    while ((c = wFile.read()) >= 0) {  //print contents
        Serial.write(c);
    }
    wFile.close();
}






void SdCard::createDummy() {
    SdFile wrfile("testwrite.txt", O_WRITE | O_CREAT | O_TRUNC);
    if (!wrfile.isOpen()) {
        Serial.print("Error");
    }
    wrfile.print(F(
                 "D10203 123456789\n"
                // "A20203 123456789\n"
                // "A30203 123456789\n"
                // "A40203 123456789\n"
                // "A50203 123456789\n"
               ));
    Serial.println(F("Done A"));
  wrfile.close();
}



}
