var byteArrayFromObject;
var instructionCounter;
var delayTime = 100;
var memorySize = 1024;
var instructions;

function uploadFile() {
    let fileThing = document.getElementById('fileUpload');
    if (fileThing.files.length == 0) {
        console.log("no file")
        return
    }
    // console.log(fileThing.files[0])
    let reader = new FileReader();
    reader.onload = function fileReadCompleated() {
        // when its done reading, reader.result will have what you want
        // console.log(reader.result)
        let size = reader.result.byteLength;
        let array = reader.result;
        if (size > memorySize) {
            size = memorySize;
            array = reader.result.slice(0, size);
        }
        array = new Int8Array(array);
        // console.log([array, size])
        for (let i = 0; i < size; i++) {
            let byte = array[i];
            // console.log(byte);
            Module.ccall('loadProgramByte', 'boolean', ['Uint8', 'boolean'], [byte, false]);
        }
        Module.ccall('loadProgramByte', 'boolean', ['Uint8', 'boolean'], [0, true]);
        // Module.ccall('loadProgram', 'boolean', ['Uint8Array', 'number'], [array, size]);
        printMemoryView();
        printRegisters();
        printInstructions();
    }
    reader.readAsArrayBuffer(fileThing.files[0])
}

function printRegisters() {
    result = Module.ccall('getRegisters', 'string')
    for (i = 0; i < 32; i++) {
        // Print register i in a 4x8 grid
    }
    document.getElementById('registers').textContent = result;
}

function printInstructions() {
    // Print the instruction list
    // Call with an offset
    // If calling with 0, that will give the instruction being called, 1 will be the one after that and so on
    instructions = Module.ccall('getInstructionStream', 'string', 'int', '0');
    // document.getElementById('instructions').textContent = instructions;
    // console.log(instructions);
    instructions = instructions.split("\n")
    hightlightInstruction(0);
}

function hightlightInstruction(index) {
    document.getElementById('instructions').textContent = instructions[index];
}

function printMemoryView() {
    // Print view of memory in a scroll box
    result = Module.ccall('getMemory', 'string')
    // console.log(result);
    document.getElementById('memory').textContent = result;
}

// function setMemorySize(sizeInBytes) {
//     memorySize = sizeInBytes;
//     console.log(memorySize);
//     console.log(memorySize - 1);
//     Module.ccall('setMemorySize', 'boolean', 'Uint16', memorySize);
// }

// function changeMemorySize() {
//     setMemorySize(parseInt(document.getElementById("memoryInput").value) * 1024);
// }

function executeOneInstruction() {
    // Call method to run one instruction
    result = Module.ccall('execute');
    hightlightInstruction(result / 4);
    printMemoryView();
    printRegisters();
}

async function executeTenInstructions() {
    for (i = 0; i < 10; i++) {
        this.executeOneInstruction()
        await delay(30);
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
        this.executeOneInstruction();
        await delay(delayTime);
        // Module.ccall('getInstructionStream', 0);
    }
}

function stopInstructions() {
    value = false;
}

function changeDelay() {
    delayTime = parseInt(document.getElementById("delayInput").value);
}

function initSim() {
    Module.onRuntimeInitialized = () => {
        // setMemorySize(memorySize);
        printInstructions();
        printMemoryView();
        printRegisters();
    };
    document.getElementById("delayInput").value = delayTime;
    // document.getElementById("memoryInput").value = memorySize/1024;
}