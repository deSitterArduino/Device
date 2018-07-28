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
    if (!_sd.begin(10)) report_error(Error::SDBEGIN);
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
        report_error(Error::SDAPPEND);
    }
}

void SdCard::read_last_record() {
    unsigned long timer = millis();
    SdFile file(_path, O_READ | O_AT_END);
    if (file.isOpen()) {
        file.seekCur(-2);
        prev_record(file);
    file.close();
    Serial.print(F("(DEBUG) REVERSE READ: "));
    Serial.print(millis() - timer);
    Serial.println(F("ms"));
    }
}

void SdCard::prev_record(SdFile& file) {
    char c = '\0';
    while (file.seekCur(-1)) {
        if ((c = file.peek()) == '\n') {
            file.seekCur(1);
            while ((c = file.read()) != ' ') {
                _record._date += c;
            }
            while ((c = file.read()) != '\r') {
                _record._barcode += c;
            }
            break;
        }
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
        report_error(Error::SDDELETE);
    }
}

void SdCard::read_file() {
    unsigned long timer = millis();
    char c = '\0';
    SdFile file(_path, O_READ);
    if (file.isOpen()) {
        while ((c = file.read()) >= 0) {  //print contents
            Serial.print(c, DEC);
            Serial.print(" ");
            Serial.print(file.curPosition());
            Serial.print(" ");
            Serial.println(c);
        }
    file.close();
    Serial.print(F("(DEBUG) FORWARD READ: "));
    Serial.print(millis() - timer);
    Serial.println(F("ms"));
    } else {
        report_error(Error::SDREAD);
    }
}

void SdCard::read_file_reverse() {
    unsigned long timerF = millis();
    char c = '\0';
    SdFile file(_path, O_READ | O_AT_END);
    if (file.isOpen()) {
        Serial.println(file.curPosition());
        while ((file.seekCur(-1)) && ((c = file.peek()) >= 0)) {  //print contents
            Serial.print(c, DEC);
            Serial.print(" ");
            Serial.print(file.curPosition());
            Serial.print(" ");
            Serial.println(c);
        }
    file.close();
    Serial.print(F("(DEBUG) REVERSE READ: "));
    Serial.print(millis() - timerF);
    Serial.println(F("ms"));
    } else {
        report_error(Error::SDREAD);
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
