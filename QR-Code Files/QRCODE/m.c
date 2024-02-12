#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <qrencode.h>

int main() {
    const char *data_to_encode = "Hello, QR Code!";
    QRcode *qrcode = QRcode_encodeString(data_to_encode, 0, QR_ECLEVEL_L, QR_MODE_8, 1);

    if (qrcode != NULL) {
        printf("QR Code generated successfully.\n");

        // Display or save the QR code as needed

        QRcode_free(qrcode);
    } else {
        printf("Error generating QR Code.\n");
    }

    return 0;
}
