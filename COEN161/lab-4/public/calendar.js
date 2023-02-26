function main(){

    let monthTitle = document.querySelector("#month-title");
    let month = 0;

    let sept = document.querySelector("#sept");
    let oct = document.querySelector("#oct");
    let nov = document.querySelector("#nov");
    let dec = document.querySelector("#dec");

    let form = document.querySelector(".month-selector");
    form.addEventListener('change', (event) => {
        if(sept.checked){
            reset();
            monthTitle.innerHTML = "September";
            month = 8;
            initialize(month);
            populate(month);
        }else if(oct.checked){
            reset();
            monthTitle.innerHTML = "October";
            month = 9;
            initialize(month);
            populate(month);
        }else if(nov.checked){
            reset();
            monthTitle.innerHTML = "November";
            month = 10;
            initialize(month);
            populate(month);
        }else if(dec.checked){
            reset();
            monthTitle.innerHTML = "December";
            month = 11;
            initialize(month);
            populate(month);
        }else{
            reset();
            monthTitle.innerHTML = "Class Schedule";
            month = 0;
            initialize(month);
            populate(month);
        }
    })

    reset();


}

//then final step is call all 3 in one fn after deciding which radio is chosen


//reset fn - make everything empty
function reset(){
    console.log('Reset Loads');
    let table = document.querySelector(".calendar-wrapper");
    for (var i = 1, row; row = table.rows[i]; i++) {
        //iterate through rows
        //rows would be accessed using the "row" variable assigned in the for loop
        for (var j = 0, col; col = row.cells[j]; j++) {
          //iterate through columns
          //columns would be accessed using the "col" variable assigned in the for loop
            col.innerHTML = "";
            col.removeAttribute('class');
        }  
     }
     console.log("Reset ends");
}


//intialization fn - figure out what month to display and get td
function initialize(month){
    let table = document.querySelector(".calendar-wrapper");
    if(month === 8){
        
        //Starts on a Thursday
        let dayCount = 1;
        let week1 = table.rows[1];
        for(let k = 4, startOfMonth; startOfMonth = week1.cells[k]; k++){
            startOfMonth.innerHTML = dayCount;
            startOfMonth.classList.add(`day${dayCount}`);
            dayCount++;
        }
        for (let i = 2, row; row = table.rows[i]; i++) {
            console.log("Row runs");
            //iterate through rows
            //rows would be accessed using the "row" variable assigned in the for loop
            for (let j = 0, col; col = row.cells[j]; j++) {
              //iterate through columns
              //columns would be accessed using the "col" variable assigned in the for loop
                if(dayCount < 31){
                    col.innerHTML = dayCount;
                    col.classList.add(`day${dayCount}`);
                    dayCount++;
                }else{
                    col.innerHTML = "";
                }
            }  
         }
    }else if(month === 9){
        //Starts on a Saturday
        let dayCount = 1;
        let week1 = table.rows[1];
        for(let k = 6, startOfMonth; startOfMonth = week1.cells[k]; k++){
            startOfMonth.innerHTML = dayCount;
            startOfMonth.classList.add(`day${dayCount}`);
            dayCount++;
        }
        for (let i = 2, row; row = table.rows[i]; i++) {
            console.log("Row runs");
            //iterate through rows
            //rows would be accessed using the "row" variable assigned in the for loop
            for (let j = 0, col; col = row.cells[j]; j++) {
              //iterate through columns
              //columns would be accessed using the "col" variable assigned in the for loop
                if(dayCount <= 31){
                    col.innerHTML = dayCount;
                    col.classList.add(`day${dayCount}`);
                    dayCount++;
                }else{
                    col.innerHTML = "";
                }
            }  
         }

    }else if(month === 10){
        //Starts on a Tuesday
        let dayCount = 1;
        let week1 = table.rows[1];
        for(let k = 2, startOfMonth; startOfMonth = week1.cells[k]; k++){
            startOfMonth.innerHTML = dayCount;
            startOfMonth.classList.add(`day${dayCount}`);
            dayCount++;
        }
        for (let i = 2, row; row = table.rows[i]; i++) {
            console.log("Row runs");
            //iterate through rows
            //rows would be accessed using the "row" variable assigned in the for loop
            for (let j = 0, col; col = row.cells[j]; j++) {
              //iterate through columns
              //columns would be accessed using the "col" variable assigned in the for loop
                if(dayCount < 31){
                    col.innerHTML = dayCount;
                    col.classList.add(`day${dayCount}`);
                    dayCount++;
                }else{
                    col.innerHTML = "";
                }
            }  
         }

    }else if(month === 11){
        //Starts on a Thursday
        let dayCount = 1;
        let week1 = table.rows[1];
        for(let k = 4, startOfMonth; startOfMonth = week1.cells[k]; k++){
            startOfMonth.innerHTML = dayCount;
            startOfMonth.classList.add(`day${dayCount}`);
            dayCount++;
        }
        for (let i = 2, row; row = table.rows[i]; i++) {
            console.log("Row runs");
            //iterate through rows
            //rows would be accessed using the "row" variable assigned in the for loop
            for (let j = 0, col; col = row.cells[j]; j++) {
              //iterate through columns
              //columns would be accessed using the "col" variable assigned in the for loop
                if(dayCount <= 31){
                    col.innerHTML = dayCount;
                    col.classList.add(`day${dayCount}`);
                    dayCount++;
                }else{
                    col.innerHTML = "";
                }
            }  
         }

    }
}

//populate events fn - uses EVENTS to populate the cal
function populate(month){
    const event = EVENTS[month];
    
    let officeCount = 0;
    let hwCount = 0;
    let quizCount = 0;
    let labCount = 0;

    for(let i = 1; i <= 32; i++){
        console.log(i);
        console.log(event[i]);
        let date = document.querySelector(`tr > .day${i}`);
        if(event[i]){
            console.log('finds event');
            if(event[i].type === "office-hours"){
                date.classList.add('office-hours');
                date.style.textDecoration = "underline";
                officeCount++;
            }else if(event[i].type === "homework"){
                date.classList.add('homework');
                date.style.textDecoration = "none";
                date.innerHTML = "";
                let span = document.createElement('span');
                date.appendChild(span);
                span.innerHTML = i;
                span.classList.add('hwSpan');
                span.style.content = i;
                hwCount++;
            }else if(event[i].type === "quiz"){
                date.classList.add('quiz');
                date.style.textDecoration = "none";
                date.innerHTML = "";
                let span = document.createElement('span');
                date.appendChild(span);
                span.innerHTML = i;
                span.classList.add('quizSpan');
                span.style.content = i;
                quizCount++;
            }else if(event[i].type === "lab"){
                date.classList.add('lab');
                date.style.textDecoration = "none";
                labCount++;
            }
        }else{
            date.style.removeProperty('text-decoration');
        }
        let legendQuiz = document.querySelector('li > .quiz');
        let legendLab = document.querySelector('li > .lab');
        let legendHW = document.querySelector('ul > li > span.hwNum');
        let legendOffice = document.querySelector('ul > li > span.officeNum');
        legendQuiz.innerHTML = quizCount;
        legendLab.innerHTML = labCount;
        legendHW.innerHTML = hwCount;
        legendOffice.innerHTML = officeCount;
        console.log("office hours: " + officeCount + "\nhw: " + hwCount + "\nquiz: " + quizCount + "\nlab: " + labCount);
    }
}

function setMonth(startDay){
    //Starts on a Thursday
    let table = document.querySelector(".calendar-wrapper");
    let dayCount = 1;
    let week1 = table.rows[1];
    for(let k = startDay, startOfMonth; startOfMonth = week1.cells[k]; k++){
        startOfMonth.innerHTML = dayCount;
        startOfMonth.classList.add(`day${dayCount}`);
        dayCount++;
    }
    for (let i = 2, row; row = table.rows[i]; i++) {
        console.log("Row runs");
        //iterate through rows
        //rows would be accessed using the "row" variable assigned in the for loop
        for (let j = 0, col; col = row.cells[j]; j++) {
          //iterate through columns
          //columns would be accessed using the "col" variable assigned in the for loop
            if(dayCount <= 31){
                col.innerHTML = dayCount;
                col.classList.add(`day${dayCount}`);
                dayCount++;
            }else{
                col.innerHTML = "";
            }
        }  
     }
}

window.addEventListener('load', main);
