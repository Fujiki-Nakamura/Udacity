/**
 * 
 * Manipulating the DOM exercise.
 * Exercise programmatically builds navigation,
 * scrolls to anchors from navigation,
 * and highlights section in viewport upon scrolling.
 * 
 * Dependencies: None
 * 
 * JS Version: ES2015/ES6
 * 
 * JS Standard: ESlint
 * 
*/
const navbar = document.getElementById('navbar__list')
const sections = document.querySelectorAll('section')
const offsetTopMain = document.querySelector('main').offsetTop
const offsetTopSection1 = sections[0].offsetTop - offsetTopMain
const offsetTopSection2 = sections[1].offsetTop - offsetTopMain
const offsetTopSection3 = sections[2].offsetTop - offsetTopMain
const offsetTopSection4 = sections[3].offsetTop - offsetTopMain
let section_id = 1

/* create button in the navigation bar.
 * add event listener to each button.
*/
for (const section of sections) {
    let li = document.createElement('li')
    li.setAttribute('class', 'menu__link')
    li.setAttribute('id', 'nav-' + section.getAttribute('id'))
    li.innerHTML = section.getAttribute('data-nav')
    li.addEventListener('click', function(event) {
        scroll(event.srcElement)
    })
    navbar.appendChild(li)
}

const buttons = document.querySelectorAll('li')


function scroll(elem) {
    // takes source element clicked, scroll to section the element points to.
    let section_id = elem.getAttribute('id').replace('nav-', '')
    let section = document.getElementById(section_id)
    window.scrollTo({
        top: section.offsetTop,
        behavior: 'smooth',
    })
}


function highlight(windowY) {
    if (offsetTopSection1 <= windowY && windowY < offsetTopSection2) {
        section_id = 1;
    } else if (offsetTopSection2 <= windowY && windowY < offsetTopSection3) {
        section_id = 2;
    } else if (offsetTopSection3 <= windowY && windowY < offsetTopSection4) {
        section_id = 3;
    } else if (offsetTopSection4 <= windowY && windowY < document.querySelector('.page__footer').offsetTop) {
        section_id = 4;
    }
    for (let i = 0; i < sections.length; i++) {
        if (i + 1 === section_id) {
            sections[i].setAttribute('class', 'your-active-class')
            buttons[i].setAttribute('class', 'menu__link active-button')
        } else {
            sections[i].setAttribute('class', '')
            buttons[i].setAttribute('class', 'menu__link')
        }
    }
}


document.addEventListener('scroll', function(event) {
    highlight(window.scrollY);
})
