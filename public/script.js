async function api(url, method = 'GET', body = null) {
    const options = { method, headers: { 'Content-Type': 'application/json' } };
    if (body) options.body = JSON.stringify(body);
    const res = await fetch(url, options);
    if (!res.ok) {
        let msg = 'API Error';
        try {
            const data = await res.json();
            msg = data.error || data.message || msg;
        } catch (e) {
            msg = await res.text() || msg;
        }
        throw new Error(msg);
    }
    return res.headers.get('content-type')?.includes('application/json') ? res.json() : res.text();
}

function showToast(msg) {
    const t = document.getElementById('toast');
    t.innerText = msg;
    t.classList.add('show');
    setTimeout(() => t.classList.remove('show'), 3000);
}

// --- Book Actions ---

async function loadBooks() {
    try {
        const books = await api('/api/books');
        const list = document.getElementById('books-list');
        list.innerHTML = books.map(b => `
            <tr>
                <td>${b.id}</td>
                <td><strong>${b.name}</strong></td>
                <td>${b.author}</td>
                <td>${b.genre}</td>
                <td><span class="status-tag ${b.isIssued ? 'issued' : 'available'}">${b.isIssued ? 'Issued' : 'Available'}</span></td>
                <td>
                    <div style="display:flex; gap:5px; flex-wrap: wrap;">
                        ${!b.isIssued ? `<button class="btn-secondary" style="padding: 4px 8px;" onclick="issuePrompt(${b.id})">Issue</button>` : `<button class="btn-secondary" style="padding: 4px 8px;" onclick="returnBook(${b.id})">Return</button>`}
                        <button class="btn-primary" style="padding: 4px 8px;" onclick="showEditModal(${b.id}, '${b.name.replace(/'/g, "\\'")}', '${b.author.replace(/'/g, "\\'")}', '${b.genre.replace(/'/g, "\\'")}')">Edit</button>
                        <button class="btn-secondary" style="padding: 4px 8px; background: #e74c3c;" onclick="deleteBook(${b.id})">Del</button>
                        <button class="btn-primary" style="padding: 4px 8px;" onclick="getRecommendations(${b.id})">💡</button>
                    </div>
                </td>
            </tr>
        `).join('');
    } catch (e) { showToast(e.message); }
}

async function searchBooks() {
    const q = document.getElementById('global-search').value;
    if (!q) return loadBooks();
    try {
        const books = await api(`/api/books/search?name=${q}`);
        const list = document.getElementById('books-list');
        list.innerHTML = books.map(b => `
            <tr>
                <td>${b.id}</td>
                <td><strong>${b.name}</strong></td>
                <td>${b.author}</td>
                <td>${b.genre}</td>
                <td><span class="status-tag ${b.isIssued ? 'issued' : 'available'}">${b.isIssued ? 'Issued' : 'Available'}</span></td>
                <td></td>
            </tr>
        `).join('');
    } catch (e) { showToast(e.message); }
}

async function addBook() {
    const body = {
        id: parseInt(document.getElementById('add-id').value) || 0,
        name: document.getElementById('add-title').value,
        author: document.getElementById('add-author').value,
        genre: document.getElementById('add-genre').value
    };
    try {
        await api('/api/books/add', 'POST', body);
        showToast('Book added!');
        hideAddModal();
        loadBooks();
    } catch (e) { showToast(e.message); }
}

// --- Issue/Return ---

async function issuePrompt(id) {
    const user = prompt("Enter borrower name:");
    if (!user) return;
    try {
        await api(`/api/issue/${id}`, 'POST', { user });
        showToast('Added to issue queue');
        loadQueue();
        loadBooks();
    } catch (e) { showToast(e.message); }
}

async function loadQueue() {
    try {
        const queue = await api('/api/issue');
        const list = document.getElementById('queue-list');
        list.innerHTML = queue.length ? queue.map(r => `
            <div class="mini-item">
                <span><strong>#${r.bookId}</strong> ${r.bookName}</span>
                <span>👤 ${r.user}</span>
            </div>
        `).join('') : '<p>No pending requests</p>';
    } catch (e) { console.error(e); }
}

async function processIssue() {
    try {
        const res = await api('/api/issue/process', 'POST');
        showToast(`Issued ${res.bookName} to ${res.user}`);
        loadQueue();
        loadBooks();
    } catch (e) { showToast(e.message); }
}

async function returnBook(id) {
    try {
        await api(`/api/return/${id}`, 'POST');
        showToast('Book returned!');
        loadHistory();
        loadBooks();
    } catch (e) { showToast(e.message); }
}

async function loadHistory() {
    try {
        const history = await api('/api/return/history');
        const list = document.getElementById('history-list');
        list.innerHTML = history.length ? history.map(r => `
            <div class="mini-item">
                <span><strong>#${r.bookId}</strong> ${r.bookName}</span>
                <span>🕒 ${r.timestamp.split(' ')[1]}</span>
            </div>
        `).join('') : '<p>No returns yet</p>';
    } catch (e) { console.error(e); }
}

// --- Recommendations ---

async function getRecommendations(providedId = null) {
    const id = providedId || document.getElementById('rec-id').value;
    if (!id) return;
    console.log("Fetching recommendations for ID:", id);
    try {
        const recs = await api(`/api/recommend/${id}`);
        console.log("Recommendations received:", recs);
        const list = document.getElementById('recommendations-list');
        list.innerHTML = recs.length ? recs.map(b => `
            <div class="rec-card">
                <h4>${b.name}</h4>
                <p>${b.author}</p>
                <small>${b.genre}</small>
            </div>
        `).join('') : '<p>No recommendations found for ID ' + id + '</p>';
    } catch (e) { 
        console.error("Recommendation error:", e);
        showToast(e.message); 
    }
}

async function addRecommendation() {
    const a = parseInt(document.getElementById('rec-book-a').value);
    const b = parseInt(document.getElementById('rec-book-b').value);
    if (!a || !b) return showToast("Please enter both Book IDs");
    
    try {
        await api('/api/recommend/add', 'POST', { bookA: a, bookB: b });
        showToast('Relationship created!');
        hideAddRecModal();
        getRecommendations(a); // Refresh to show the new link
    } catch (e) { showToast(e.message); }
}

async function updateBook() {
    const body = {
        id: parseInt(document.getElementById('edit-id').value),
        name: document.getElementById('edit-title').value,
        author: document.getElementById('edit-author').value,
        genre: document.getElementById('edit-genre').value
    };
    try {
        await api('/api/books/update', 'POST', body);
        showToast('Book updated!');
        hideEditModal();
        loadBooks();
    } catch (e) { showToast(e.message); }
}

async function deleteBook(id) {
    if (!confirm(`Are you sure you want to delete book #${id}?`)) return;
    try {
        await api('/api/books/delete', 'POST', { id });
        showToast('Book deleted!');
        loadBooks();
    } catch (e) { showToast(e.message); }
}

// --- UI Helpers ---

function showAddModal() { document.getElementById('add-modal').style.display = 'flex'; }
function hideAddModal() { document.getElementById('add-modal').style.display = 'none'; }

function showAddRecModal() { document.getElementById('add-rec-modal').style.display = 'flex'; }
function hideAddRecModal() { document.getElementById('add-rec-modal').style.display = 'none'; }

function showEditModal(id, title, author, genre) {
    document.getElementById('edit-id').value = id;
    document.getElementById('edit-title').value = title;
    document.getElementById('edit-author').value = author;
    document.getElementById('edit-genre').value = genre;
    document.getElementById('edit-modal').style.display = 'flex';
}
function hideEditModal() { document.getElementById('edit-modal').style.display = 'none'; }

// --- Init ---
loadBooks();
loadQueue();
loadHistory();
setInterval(() => { loadQueue(); loadHistory(); }, 5000); // Poll for updates
