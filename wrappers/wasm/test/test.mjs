import pdgl_wasm from "./pdgl_wasm.js";

class Pdgl_js {
    constructor(lang, stack, seeds) {
        this.__lang = lang;
        this.__stack = stack;
        this.__seeds = seeds;
        this.__line = "";
    }

    lines = [];

    __stdin = () => {
        // Return ASCII code of character, or null if no input
    };

    __stdout = (asciiCode) => {
        if ((asciiCode == 13) | (asciiCode == 10)) {
            this.lines.push(this.__line);
            this.__line = "";
        } else {
            this.__line += String.fromCharCode(asciiCode);
        }
    };

    __stderr = (asciiCode) => {
        // Do something with the asciiCode
    };

    run = async () => {
        let pdglwasm = await pdgl_wasm({ stdin: this.__stdin, stdout: this.__stdout });
        this.__seeds.forEach((seed) => {
            let pdgl = new pdglwasm.PDGL(this.__lang, this.__stack, seed);
            try {
                pdgl.run();
            } finally {
                pdgl.delete();
            }
        });
        return this.__lines;
    };
}
export default Pdgl_js;
