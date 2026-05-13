const canvas = document.getElementById("gridCanvas");
const ctx = canvas.getContext("2d");

canvas.width = 600;
canvas.height = 600;

const rows = 10;
const cols = 10;

const cellSize = 60;

const grid = [];

for (let i = 0; i < rows; i++) {

  grid[i] = [];

  for (let j = 0; j < cols; j++) {

    grid[i][j] = 0;

  }

}

const obstacles = [
  [3,3],
  [3,4],
  [3,5],
  [5,6],
  [6,6],
  [7,6]
];

obstacles.forEach(([x, y]) => {

  grid[x][y] = 1;

});

const path = [
  [0,0],
  [1,0],
  [2,0],
  [2,1],
  [2,2],
  [2,3],
  [2,4],
  [2,5],
  [2,6],
  [3,6],
  [4,6],
  [4,7],
  [5,7],
  [6,7],
  [7,7],
  [8,7],
  [9,7],
  [9,8],
  [9,9]
];

function drawGrid() {

  for (let i = 0; i < rows; i++) {

    for (let j = 0; j < cols; j++) {

      ctx.strokeStyle = "#444";

      ctx.strokeRect(
        j * cellSize,
        i * cellSize,
        cellSize,
        cellSize
      );

      if (grid[i][j] === 1) {

        ctx.fillStyle = "red";

        ctx.fillRect(
          j * cellSize,
          i * cellSize,
          cellSize,
          cellSize
        );

      }

    }

  }

}

let robotStep = 0;

function animateRobot() {

  ctx.clearRect(0,0,canvas.width,canvas.height);

  drawGrid();

  // Draw path
  path.forEach(([x, y]) => {

    ctx.fillStyle = "#2d7cff55";

    ctx.fillRect(
      y * cellSize,
      x * cellSize,
      cellSize,
      cellSize
    );

  });

  const [rx, ry] = path[robotStep];

  // Draw robot
  ctx.beginPath();

  ctx.arc(
    ry * cellSize + cellSize/2,
    rx * cellSize + cellSize/2,
    18,
    0,
    Math.PI * 2
  );

  ctx.fillStyle = "dodgerblue";
  ctx.fill();

  // Start
  ctx.fillStyle = "limegreen";
  ctx.fillRect(0,0,cellSize,cellSize);

  // End
  ctx.fillStyle = "gold";
  ctx.fillRect(
    9 * cellSize,
    9 * cellSize,
    cellSize,
    cellSize
  );

  robotStep++;

  if (robotStep >= path.length) {

    robotStep = 0;

  }

}

setInterval(animateRobot, 300);