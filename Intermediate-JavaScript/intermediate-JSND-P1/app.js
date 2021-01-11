// Create Dino Constructor
function Dinosaur(species, weight, height, diet, where, when, fact) {
    this.species = species
    this.weight = weight
    this.height = height
    this.diet = diet
    this.where = where
    this.when = when
    this.facts = [fact, `${species} lived in ${where}.`, `${species} lived during ${when}.`]
}

// Create Dino Objects
async function createDinos() {
    let data = await fetch("https://raw.githubusercontent.com/udacity/Javascript/master/dino.json")
        .then(response => response.json())
        .catch(err => console.log(err))
    dinos = data.Dinos.map(
        dino => new Dinosaur(dino.species, dino.weight, dino.height, dino.diet, dino.where, dino.when, dino.fact))
    return dinos
}
let dinos = createDinos()

// Create Human Object
// Use IIFE to get human data from form
// NOTE: not using IIFE currently. Get input values later when the button is pushed.
function createHuman () {
    this.name = document.getElementById("name").value
    this.feet = parseInt(document.getElementById("feet").value)
    this.inches = parseInt(document.getElementById("inches").value)
    this.height = 12 * feet + inches
    this.weight = parseInt(document.getElementById("weight").value)
    this.diet = document.getElementById("diet").value.toLowerCase()
}

// Create Dino Compare Method 1
// NOTE: Weight in JSON file is in lbs, height in inches. 
Dinosaur.prototype.compareWeight = function (human) {
    const factor = Math.round(parseFloat(this.weight) / parseFloat(human.weight))
    let comparison = ""
    if (this.weight > human.weight) {
        comparison = `${this.species} is ${factor} times heavier than ${human.name}`
    } else if (this.weight < human.weight) {
        comparison = `${this.species} is ${factor} times lighter than ${human.name}`
    } else {
        comparison = `${this.species} is as heavy as ${human.name}`
    }
    this.facts.push(comparison)
}

// Create Dino Compare Method 2
// NOTE: Weight in JSON file is in lbs, height in inches.
Dinosaur.prototype.compareHeight = function (human) {
    const factor = Math.round(parseFloat(this.height) / parseFloat(human.height))
    let comparison = ""
    if (this.height > human.height) {
        comparison = `${this.species} is ${factor} times taller than ${human.name}`
    } else if (this.height < human.height) {
        comparison = `${this.species} is ${factor} times shorter than ${human.name}`
    } else {
        comparison = `${this.species} is as tall as ${human.name}`
    }
    this.facts.push(comparison)
}

// Create Dino Compare Method 3
// NOTE: Weight in JSON file is in lbs, height in inches.
Dinosaur.prototype.compareDiet = function (human) {
    const humanDiet = human.diet.toLowerCase()
    let comparison = ""
    if (this.diet === humanDiet) {
        comparison = `${this.species} has the same diet (${this.diet}) as ${human.name}"`
    } else {
        comparison = `${this.species} has different diet (${this.diet}) from ${human.name} (${humanDiet})`
    }
    this.facts.push(comparison)
} 

// Generate Tiles for each Dino in Array
// Add tiles to DOM
function addTiles(objects) {
    const grid = document.getElementById("grid")
    objects.map(obj => {
        let gridItem = document.createElement("div")
        gridItem.className = "grid-item"

        // Name
        let gridItemH = document.createElement("h3")
        let name = (obj.species) ? obj.species : obj.name
        gridItemH.appendChild(document.createTextNode(name))
        gridItem.appendChild(gridItemH)

        let gridItemImg = document.createElement("img")
        gridItemImg.src = (obj.species) ? `./images/${name.toLowerCase()}.png` : `./images/human.png`
        gridItem.appendChild(gridItemImg)

        let gridItemFact = document.createElement("p")
        let fact = ""
        if (obj.species) {
            if (name.toLowerCase() === "pigeon") fact = obj.facts[0]
            else fact = obj.facts[Math.floor(Math.random() * obj.facts.length)]
        }
        gridItemFact.appendChild(document.createTextNode(fact))
        gridItem.appendChild(gridItemFact)

        grid.append(gridItem)
    })
}

// Remove form from screen
function removeForm() {
    let form = document.getElementById("dino-compare")
    form.innerHTML = ""
}

// On button click, prepare and display infographic
const button = document.getElementById("btn")
button.addEventListener("click", (function () {
    // Create human object
    const human = new createHuman()
    // Compare
    dinos.map(dino => {
        dino.compareWeight(human)
        dino.compareHeight(human)
        dino.compareDiet(human)
    })
    // Remove form
    removeForm()
    // Add tiles
    dinos.splice(4, 0, human)
    addTiles(dinos)
}))
