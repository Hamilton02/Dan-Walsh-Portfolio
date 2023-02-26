//Danny Walsh
//COEN 161
//Lab 3

//Question 1: I used defer to not block the parser
//Question 2: What happens when there's an error message, the Console.log runs before the chart external script because it's put in the callback queue
//Question 3: setInterval puts the function in the callback queue and once the call stack is done, it will check the setInterval timer and execute it if it's timer is done
//Question 4: That would never pass anything onto the call stack and the callback queue would be jammed
//Question 5: 100 ms

let interval = setInterval(main(), 100);

function main(interval) {
    if (!Chart){
        console.log(Chart)
    } else {
        clearInterval(interval)
    }

    createGradeByWeekChart();

    createPointsInClassChart();

    createPointsByCategoryChart();

}



function createGradeByWeekChart(){
    const canvas = document.querySelector("#grade-by-week");

    let options= {
        type: "line",
        data: {
            // which axis shows these labels?
            labels: [
                "1", "2", "3", "4", "5", "6", "7", "8", "9", "10"
            ],
            xAxisID: "Week",
            yAxisID: "Grade",
            datasets: [
            // is this the top or bottom data set?
            // what happens if there's only 1 dataset?
                {
                    label: "Grade",
                    data: [80, 77, 62, 81, 85, 90, 84, 73, 80, 90],
                    backgroundColor: "rgba(155, 89, 182, 1.0)",
                    borderColor: "rgba(155, 89, 182, 1.0)",
                },
                {
                    label: "Missed",
                    data: [20, 23, 38, 19, 15, 10, 16, 27, 20, 10],
                    backgroundColor: "rgba(200, 200, 200, 1.0)",
                },
                
            ],
        },
        options: {
            scales: {
                y: {
                    stacked: false,
                    grid: {
                        display: false,
                    },
                    min: 0,
                    max: 100,
                    title:{
                        display: true,
                        text: "Grades",
                    },
                },
                x: {
                    stacked: true,
                    grid: {
                        display: false,
                    },
                    title:{
                        display: true,
                        text: "Week",
                    },
                },
            },
            aspectRatio: 1,
            plugins: {
                title: {
                    display: true,
                    text: "Grades by Week",
                },
                legend: {
                    display: true,
                },
            },
        },
    };

    const chart = new Chart(canvas.getContext("2d"), options);

}

function createPointsInClassChart(){
    const canvas = document.querySelector("#points-in-class");

    let options= {
        type: "pie",
        data: {
            // which axis shows these labels?
            labels: ["Earned" , "Missing"],
            datasets: [
            // is this the top or bottom data set?
            // what happens if there's only 1 dataset?
                {
                    label: "Grade",
                    data: [70, 30],
                    backgroundColor: [
                        "rgba(155, 89, 182, 1.0)",
                        "rgba(100, 89, 182, 1.0"
                    ],
                    hoverBackgroundColor: [
                        "rgba(155, 89, 182, 0.5)",
                        "rgba(100, 89, 182, 0.5"
                    ],
                    hoverOffset:[
                        7, 3

                    ]
                },
                
            ],
        },
        options: {
            scales: {
            },
            x: {
                stacked: true,
                grid: {
                    display: false,
                },
            },
            aspectRatio: 1,
            plugins: {
                title: {
                    display: true,
                    text: "Points in Class",
                },
                legend: {
                    display: false,
                },
            },
        },
    };

    const chart = new Chart(canvas.getContext("2d"), options);

}

function createPointsByCategoryChart(){
    const canvas = document.querySelector("#points-by-category");

    let options= {
        // the type of chart we want to use
        type: "bar",
        data: {
            // which axis shows these labels?
            labels: ["Quizzes", "Labs", "Theory", "Practice"],
            datasets: [
            // is this the top or bottom data set?
            // what happens if there's only 1 dataset?
                {
                    label: "Earned",
                    data: [65, 59, 80, 81, 56, 55, 40],
                    backgroundColor: "rgba(155, 89, 182, 1.0)",
                },
                {
                    label: "Missed",
                    data: [65, 59, 80, 81, 56, 55, 40],
                    backgroundColor: "rgba(155, 89, 182, 0.5)",
                },
                {
                    label: "Ungraded",
                    data: [65, 59, 80, 81, 56, 55, 40],
                    backgroundColor: "#eee",
                },
            ],
        },
        options: {
            scales: {
                y: {
                    stacked: true,
                    grid: {
                        display: false,
                    },
                },
            },
            x: {
                stacked: true,
                grid: {
                    display: false,
                },
            },
            aspectRatio: 1,
            plugins: {
                title: {
                    display: true,
                    text: "Points by Category",
                },
                legend: {
                    display: false,
                },
            },
        },
    };

    const chart = new Chart(canvas.getContext("2d"), options);

}

