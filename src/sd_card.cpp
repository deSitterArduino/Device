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
    if (!_sd.begin(10)) report_error("error SD begin");
}

void SdCard::append_record(const String date, const String barcode) {
    SdFile file(_path, O_RDWR | O_CREAT);
    if (file.isOpen()) {
        int records = parse_header(file);
        file.seekEnd();
        file.print(date);
        file.write(" ");
        file.println(barcode);
        write_header(file, ++records);
        file.close();
    } else {
        report_error("error opening file to append");
    }
}

void SdCard::write_header(SdFile& file, const int num) {
    Serial.println(F("(DEBUG) Entered writeNumRecords"));
    file.rewind();
    String header = String(num);
    Serial.print(F("(DEBUG) Current header before append: "));
    Serial.println(header);
    while (header.length() < _headerSize) {
        header += '\0';    //append null characters till header.length = _headerSize
    }
    Serial.print(F("DEBUG) Header after append: "));
    Serial.println(header);
    header += '\r';
    header += '\n';
    file.print(header);
}

int SdCard::parse_header(SdFile& file) {
    Serial.println(F("(DEBUG) Entered parsehNumRecords"));
    if (file.fileSize() == 0) {     //file has just been created
        Serial.println(F("(DEBUG) FileSize = 0"));
        return 0;
    } else {
        char c = '\0';
        String num = "";
        file.rewind();
        while ((c = file.read()) >= 0) {
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

void SdCard::delete_file() {
    if (_sd.exists(_path)) {
        SdFile file(_path, O_RDWR);
        file.remove();
        file.close();
        Serial.print("(DEBUG) Deleted");
    } else {
        report_error("error deleting, file does not exist");
    }
}

void SdCard::read_file() {
    char c = '\0';
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
        report_error("error opening file to read");
    }
}






void SdCard::delete_record(int n) {
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

}
