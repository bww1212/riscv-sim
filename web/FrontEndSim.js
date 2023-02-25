class FrontEndSim {
    byteArrayFromObject;

    uploadFile() {
        fileExtension = fileupload.split('.').pop();
        if (fileExtension != 'o') {
            window.alert("Please enter an object file.");
            return null;
        }
    }

    parseFile(file) {
        return new Promise((resolve, reject) => {
            try {
                var reader = new FileReader();
                let byteArray = [];
                reader.readAsArrayBuffer(file);
                reader.onloadend = (evt) => {
                    if (evt.target.readyState == FileReader.DONE) {
                        let buffer = evt.target.result,
                        array = new Uint8Array(buffer);
                        for (byte of array) {
                            byteArray.push(byte);
                        }
                    }
                    resolve(byteArray);
                }
            }
            catch (e) {
                reject(e);
            }
        })
    }
}