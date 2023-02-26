var byteArrayFromObject;
var instructionCounter;
var delayTime;

function uploadFile() {
    fileExtension = document.getElementById("fileUpload").split('.').pop();
    if (fileExtension != 'o') {
        window.alert("Please enter an object file.");
        return null;
    }
}

function parseFile(file) {
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

function printRegisters() {
    for (i = 0; i < 32; i++) {
        // Print register i in a 4x8 grid
    }
}

function printInstructions() {
    // Print the instruction list
    // Call with an offset
    // If calling with 0, that will give the instruction being called, 1 will be the one after that and so on
    
}

function printMemoryView() {
    // Print view of memory in a scroll box
}

function setMemorySize(sizeInBytes) {
    // Call method to set memory size
}

function executeOneInstruction() {
    // Call method to run one instruction
    Module.cwrap('getInstructionStream', '0');
}

function executeTenInstructions() {
    for (i = 0; i < 10; i++) {
        this.executeOneInstruction()
    }
}

function delay(milliseconds) {
    return new Promise(resolve => {
        setTimeout(() => {resolve('')}, milliseconds);
    })
}

async function playInstructions() {
    value = true;
    while (value) {
        this.executeOneInstruction()
        await delay(delayTime);
        console.log(delayTime);
    }
}

function stopInstructions() {
    value = false;
}

function changeDelay() {
    delayTime = parseInt(document.getElementById("delayInput").value);
}
