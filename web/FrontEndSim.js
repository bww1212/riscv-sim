class FrontEndSim {
    byteArrayFromObject;
    instructionCounter;
    delayTime;

    uploadFile() {
        fileExtension = document.getElementById("fileUpload").split('.').pop();
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

    printRegisters() {
        for (i = 0; i < 32; i++) {
            // Print register i in a 4x8 grid
        }
    }

    printInstructions() {
        // Print the instruction list
        // Call with an offset
        // If calling with 0, that will give the instruction being called, 1 will be the one after that and so on
    }

    printMemoryView() {
        // Print view of memory in a scroll box
    }

    setMemerySet(sizeInBytes) {
        // Call method to set memory size
    }

    executeOneInstruction() {
        // Call method to run one instruction
    }

    executeTenInstructions() {
        for (i = 0; i < 10; i++) {
            // Call the method to run one instruction
        }
    }

    playInstructions() {
        while (value) {
            // Method to execute one instruction
            delay(delayTime);
        }
    }

    stopInstructions() {
        value = false;
    }

    changeDelay() {
        delayTime = parseInt(document.getElementById("delayInput").content);
    }
}