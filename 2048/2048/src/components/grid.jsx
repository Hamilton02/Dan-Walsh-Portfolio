import React, {useState} from 'react';
import Box from './box';
import "../App.css"

export default class grid extends React.Component{
        

    constructor(props){
        super(props);
        this.state = {
            counter: 0,
        };
        
    }
    
    increment() {
        this.setState(state => ({
            counter: state.counter+1
        }));
    }

    generateGrid(){
        let cols = [];
        let rows = [];
        for(let i = 0; i < 4; i++){
            
            rows[i] = cols[i];
            for(let j = 0; j < 4; j++){
                cols[j] = <Box></Box>;
            }
            
            rows[i] = cols;
            
        }

            return rows;
    
    }

    render() {
    
        let rows = this.generateGrid();    

        return (<div className="grid">
            {rows.map((rows, index) => {
                return (
                <div className="row">
                    {rows.map((boxes, sIndex) => {
                    return <p>{boxes}</p>;
                    })}
                </div>
                );
            })}
            </div>);
    }
    
}


